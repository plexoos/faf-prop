#include <algorithm>
#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TTree.h"

#include "g4main/PHG4TruthInfoContainer.h"
#include "g4main/PHG4Particle.h"
#include "g4main/PHG4Shower.h"


struct ParsedArgs
{
  bool valid;
  std::string prg_name;
  std::string fpath1;
  std::string fpath2;
  operator bool() const { return valid; }
};

struct RootInput
{
  std::unique_ptr<TFile> file;
  std::unique_ptr<TBranch> branch;
};

struct DiffCount
{
  int particles, vertices, showers;
  int particles1, vertices1, showers1;
  int particles2, vertices2, showers2;
  operator bool() const { return particles > 0 || vertices > 0 || showers > 0; }
  friend std::ostream& operator<<(std::ostream& os, const DiffCount& d)
  {
    return os << d.particles  << ' ' << d.vertices  << ' ' << d.showers << '\n'
              << d.particles1 << ' ' << d.vertices1 << ' ' << d.showers1 << '\n'
              << d.particles2 << ' ' << d.vertices2 << ' ' << d.showers2;
  }
};


ParsedArgs ParseArgs(int argc, char **argv);
RootInput FindBranch(std::string bname, std::string fpath);
DiffCount Diff(const PHG4TruthInfoContainer& c1, const PHG4TruthInfoContainer& c2);


int main(int argc, char **argv)
{
  auto args = ParseArgs(argc, argv);

  if (!args)
  {
    std::cout << "usage: " << args.prg_name << " fpath1 fpath2\n";
    return EXIT_FAILURE;
  }

  std::cout << "file1: " << args.fpath1 << '\n'
            << "file2: " << args.fpath2 << '\n';

  std::string bname("DST#G4TruthInfo");

  RootInput inp1 = FindBranch(bname, args.fpath1);
  RootInput inp2 = FindBranch(bname, args.fpath2);

  if (!inp1.branch || !inp2.branch)
    return EXIT_FAILURE;

  auto* branch_container1 = new PHG4TruthInfoContainer();
  auto* branch_container2 = new PHG4TruthInfoContainer();

  inp1.branch->SetAddress(&branch_container1);
  inp2.branch->SetAddress(&branch_container2);

  int nrecords1 = inp1.branch->GetEntries();
  int nrecords2 = inp2.branch->GetEntries();
  int nrecords = std::min({nrecords1, nrecords2, 10});

  std::cout << "Number of records in file1 and file2: " << nrecords1 << " and " << nrecords2
            << ". Will compare first " << nrecords << " records\n";

  DiffCount diff{};
  int irecord = 0;

  for ( ; irecord < nrecords; ++irecord)
  {
    inp1.branch->GetEntry(irecord);
    inp2.branch->GetEntry(irecord);

    diff = Diff(*branch_container1, *branch_container2);

    if (diff)
      break;
  }

  if (diff) {
    std::cout << "diff: " << irecord << ": " << diff << '\n';
    return irecord;
  }

  return EXIT_SUCCESS;
}


ParsedArgs ParseArgs(int argc, char **argv)
{
  bool valid = true;

  std::string prg_name(argv[0]);
  prg_name.erase(0, prg_name.find_last_of('/')+1);

  std::string fpath1( argc > 1 ? argv[1] : "" );
  std::string fpath2( argc > 2 ? argv[2] : "" );

  if (!std::ifstream(fpath1).is_open()) {
    std::cerr << "Error: Data file \"" << fpath1 << "\" not found\n";
    valid &= false;
  }

  if (!std::ifstream(fpath2).is_open()) {
    std::cerr << "Error: Data file \"" << fpath2 << "\" not found\n";
    valid &= false;
  }

  valid &= !fpath1.empty() && !fpath2.empty() && !(fpath1 == fpath2);

  return ParsedArgs{valid, prg_name, fpath1, fpath2};
}


RootInput FindBranch(std::string bname, std::string fpath)
{
  auto file = std::make_unique<TFile>(fpath.c_str());

  if (!file)
  {
    std::cerr << "Error: Cannot open file \"" << fpath << "\"\n";
    return RootInput{nullptr, nullptr};
  }

  TTree* tree = nullptr;
  file->GetObject("T", tree);

  if (!tree)
  {
    std::cerr << "Error: TTree \"T\" not found in " << fpath << "\n";
    return RootInput{std::move(file), nullptr};
  }

  auto branch = std::unique_ptr<TBranch>(tree->GetBranch(bname.c_str()));

  if ( !(branch && branch->GetEntries() > 0) )
  {
    std::cerr << "Error: Branch \"" << bname << "\" does not exist or has 0 entries in " << fpath << "\n";
    return RootInput{std::move(file), nullptr};
  }

  return RootInput{std::move(file), std::move(branch)};
}


DiffCount Diff(const PHG4TruthInfoContainer& c1, const PHG4TruthInfoContainer& c2)
{
  auto count_mismatches = [](const auto& c1, const auto& c2, auto& counter)
  {
    auto first1 = c1.begin(), last1 = c1.end();
    auto first2 = c2.begin(), last2 = c2.end();

    for ( ; first1 != last1 && first2 != last2; ++first1, ++first2)
    {
      if (*first1 != *first2) counter++;
    }
  };

  DiffCount diff{};

  diff.particles1 = c1.GetMap().size();
  diff.particles2 = c2.GetMap().size();
  count_mismatches(c1.GetMap(), c2.GetMap(), diff.particles);

  diff.vertices1 = c1.GetVtxMap().size();
  diff.vertices2 = c2.GetVtxMap().size();
  count_mismatches(c1.GetVtxMap(), c2.GetVtxMap(), diff.vertices);

  diff.showers1 = c1.GetShowerMap().size();
  diff.showers2 = c2.GetShowerMap().size();
  count_mismatches(c1.GetShowerMap(), c2.GetShowerMap(), diff.showers);

  return diff;
}
