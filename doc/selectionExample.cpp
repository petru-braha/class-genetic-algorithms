#include<iostream>
#include<chrono>
#include<random>
#include<vector>
#include<map>
#include<algorithm>
#include<utility>
#include<functional>
#include<numeric>

using namespace std;
mt19937_64 g_randomGenerator;
normal_distribution<double> g_distribution(0, 200); //miu, sigma. and we'll use a simpler distribution in this example

void initRandomGenerator(long int additional = 0) { //we can add a number to the seed, such as the number of the run, to ensure different seeds
  mt19937_64 initGenerator;
  unsigned long int seed = static_cast<long unsigned int>( std::chrono::high_resolution_clock::now().time_since_epoch().count() ) + additional;
  initGenerator.seed(seed); //we use a secondary generator
  initGenerator.discard(10000); //and move away from the start
  g_randomGenerator.seed( initGenerator() ); //so that possibly similar seeds still yield uncorrelated random sequences
}

float rand01(int resolution = 10000) {
  return g_randomGenerator() % resolution / float(resolution); //basic, could be improved
}

//helper function to print a vector
template <class T>
inline void printVec(const vector<T>& vec, const char* header = "", const char* sep = " ", const char* end = "\n") {
  cout<<header;
  for(const auto & e: vec) {
    cout<<e<<sep;
  }
  cout<<end;
}

//helper function to print two vectors in a 1-to-1 relationship (i.e. 'zipped')
template <class T1, class T2>
inline void printZipped(const vector<T1>& vec1, const vector<T2>& vec2, const char* header = "", const char* sep = " ", const char* end = "\n", const char* map = "->") {
  cout<<header;
  for(size_t ii = 0; ii < vec1.size() && ii < vec2.size(); ++ii) {
    cout<<vec1[ii]<<map<<vec2[ii]<<sep;
  }
  cout<<endl;
}

//basic fitness-proportinal selection, once we have the accumulate probability vector
int select(const vector<float>& PC) {
  float r = rand01();
  int selected = PC.size() - 1;
  for(int ii = 0; ii < PC.size(); ++ii) {
    if(r <= PC[ii]) {
      selected = ii;
      break;
    }
  }
  return selected;
}

vector<float> generatePopulation(size_t popSize = 100) {
  vector<float> E;
  E.reserve(popSize);
  //we can emulate a distribution ourselves
  //generate_n( back_inserter(E), popSize, ref(g_randomGenerator) );
  //int resolution = 10000;
  //generate_n( back_inserter(E), popSize, [resolution]() -> float { return(g_randomGenerator() % (1025 * resolution) / float(resolution) - 512.0f); } );

  //or use the std-included distribution; in this case a normal distribution.
  //generate_n( back_inserter(E), popSize,  []() -> float { float val = g_distribution(g_randomGenerator); if(val < -512) val = 512; if(val > 512) val = 512; return val; } );

  //or have a simpler distribution, for much simpler viewing this example
  normal_distribution<float> distribution(5, 3); //miu, sigma
  generate_n( back_inserter(E), popSize,  [&distribution]() -> float { float val = int( distribution(g_randomGenerator) ); if(val < 0) val = 0; if(val > 9) val = 9; return val; } );
  return E;
}

void displayWheel(const vector<float> &E, const vector<float> &Prob) {
  map<float, float> wheel;
  for(int ii = 0; ii < E.size(); ++ii) {
    wheel[ E[ii] ] += Prob[ii];
  }

  cout<<"Summed selection probabilities for each value:\n\t";
  for(const auto& [key, value]: wheel)
    cout<<key<<": "<<value<<" ";
  cout<<endl<<endl;
}

//it's fake becaue we start with the evaluation, not with the actual population. we don't care about the GA here, we just want to see how selection changes the population.
vector<float> fakeSelection(const vector<float> &E, size_t popSize, float selectionPressure = 1, bool verbose = true) {
  const auto [emin, emax] = minmax_element( E.begin(), E.end() );
  vector<float> F;
  F.reserve( E.size() );
  //transform Evaluation into Fitness. selectionPressure is an exponent, the higher it is, the more selection favours the better evaluations.
  transform(E.begin(), E.end(), back_inserter(F), [emin, emax, &selectionPressure](float e) -> float { return pow( (*emax - e) / (*emax - *emin + 0.00001) + 1, selectionPressure ); });
  if(verbose) {
    printVec(E, "E: ");
    printZipped(E, F, "E->F:\n\t");
  }
  //normalise Fitness, yielding the actual selection probabilities
  float fs = accumulate( F.begin(), F.end(), 0.0f );
  transform(F.begin(), F.end(), F.begin(), [fs](float f) -> float { return f / fs; });
  if(verbose) {
    printZipped(E, F, "E->Fn:\n\t");
    cout<<accumulate(F.begin(), F.end(), 0.0f)<<endl;
  }
  
  displayWheel(E, F);

  //accumulate probabilities
  vector<float> PC;
  PC.reserve( F.size() );
  float prev = 0;
  //we do need an external value, outside the lambda, so each lambda can start from the previous summed probability
  transform(F.begin(), F.end(), back_inserter(PC), [&prev](float f) -> float { prev = prev + f; return prev; } );
  if(verbose) printZipped(F, PC, "F->PC:\n\t");

  //select the indices
  vector<int> newPopIndices;
  newPopIndices.reserve(popSize);
  generate_n( back_inserter(newPopIndices), popSize, [&PC]() -> int { return select(PC); } );
  if(verbose) printVec(newPopIndices, "newPopIndices:\n\t");

  //create a frequency vector
  vector<unsigned int> indexFrequencies(PC.size(), 0);
  for(auto const& index: newPopIndices)
    ++indexFrequencies[index];
  if(verbose) printZipped(E, indexFrequencies, "E->indexFrequencies:\n\t");

  //actually instantiate the next population based on the indices.
  //You don't really need to go through the intermediary indexing step,
  //I've just done it to show the changing frequencies.
  vector<float> newE;
  newE.reserve(popSize);
  int ii = 0;
  generate_n( back_inserter(newE), popSize, [&E, &newPopIndices, &ii]() -> float { return E[ newPopIndices[ii++] ]; } );
  return newE;
}

int main(int argc, char* argv[]) {
  size_t popSize = 10;
  float selectionPressure = 1;
  if(argc > 1) selectionPressure = stof(argv[1]);
  initRandomGenerator( (argc > 2)? stoi(argv[2]) : 0 ); //make the run number influece the random seed
  auto E = generatePopulation(popSize); //generate the fake population (the Evaluations)

  E = fakeSelection(E, popSize, selectionPressure, true);  //select once. the last parameter means verbose display
  printVec(E, "E: ");
  auto [emin, emax] = minmax_element( E.begin(), E.end() );
  double diff = *emax - *emin;
  do {
    E = fakeSelection(E, popSize, selectionPressure, false); //select without verbose display
    printVec(E, "E: "); //and just print the evaluation vector
    auto [emin, emax] = minmax_element( E.begin(), E.end() );
    diff = *emax - *emin;
  } while(diff > 0.001); //until the difference between max and min evaluation becomes very small, i.e. the population converges
  return 0;
}

