// Thanks to Charles Ofria for this piece of code, started usage 11/18/2002
// Slight modifications by Jason Stredwick 11/18/2002
//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1993 - 2000 California Institute of Technology             //
//                                                                          //
// Read the COPYING and README files, or contact 'avida@alife.org',         //
// before continuing.  SOME RESTRICTIONS MAY APPLY TO USE OF THIS FILE.     //
//////////////////////////////////////////////////////////////////////////////
#include "random.h"

#ifdef VISUAL_STUDIO
#include <process.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Constants //////////////////////////////////////////////////////////////////

// Statistical Approximation
 //if < n*p*(1-p)
const unsigned int RandomNumberGenerator::_BINOMIAL_TO_NORMAL=50;
const unsigned int RandomNumberGenerator::_BINOMIAL_TO_POISSON=1000; //if < n

// Engine
const unsigned int RandomNumberGenerator::_RAND_MBIG=1000000000;
const unsigned int RandomNumberGenerator::_RAND_MSEED=161803398;

// Number Generation
const double RandomNumberGenerator::_RAND_FAC=(1.0/_RAND_MBIG);
const double RandomNumberGenerator::_RAND_mP_FAC=(_RAND_MBIG/1000);
const double RandomNumberGenerator::_RAND_uP_FAC=(_RAND_MBIG/1000000);


// Constructor and setup //////////////////////////////////////////////////////

RandomNumberGenerator::RandomNumberGenerator(const int in_seed) :
  seed(0), original_seed(0), inext(0), inextp(0), use_count(0), expRV(0){
  for( int i=0; i<56; ++i ){
    ma[i] = 0;
  }
  ResetSeed(in_seed);  // Calls init()

  return;
}


void RandomNumberGenerator::ResetSeed(const int in_seed){
  //if( in_seed<0 ){  // @TCC - make 0 also be seeded with time * pid
  original_seed = in_seed;
  
  if( in_seed<=0 ){
    int seed_time = (int) time(NULL);
#ifdef VISUAL_STUDIO
    int seed_pid = (int) _getpid(); 
#else
    int seed_pid = (int) getpid(); 
#endif
    seed = seed_time ^ (seed_pid << 8);
  } else {
    seed = in_seed;
  }
  
  if( seed < 0 ) {
    seed *= -1;
  }
  seed %= _RAND_MSEED;

  init();
  initStatFunctions();

  return;
}


void RandomNumberGenerator::init(void){
  int mj, mk, ii, i;

  // does not include use_count
  d_state.reserve(60);

  // Clear variables
  inext = 0;
  inextp = 0;
  expRV = 0;
  for(i=0; i<56; ++i){
    ma[i] = 0;
  }

  mj = _RAND_MSEED - seed;
  mj %= _RAND_MBIG;
  ma[55] = mj;
  mk = 1;

  for(i=1; i<55; ++i) {
    ii = (21 * i) % 55;
    ma[ii] = mk;
    mk = mj - mk;
    if (mk < 0) {
      mk += _RAND_MBIG;
    }
    mj = ma[ii];
  }

  for (int k = 0; k < 4; ++k) {
    for (int j = 1; j < 55; ++j) {
      ma[j] -= ma[1 + (j + 30) % 55];
      if(ma[j] < 0) {
	ma[j] += _RAND_MBIG;
      }
    }
  }

  inext = 0;
  inextp = 31;

  return;
}

void RandomNumberGenerator::initStatFunctions(void){
  // Setup variables used by Statistical Distribution functions
  expRV=-log(GetDouble());

  return;
}
  

// Statistical functions //////////////////////////////////////////////////////

double RandomNumberGenerator::GetRandNormal(void){
  // Draw from a Unit Normal Dist
  // Using Rejection Method and saving of initial exponential random variable
  double expRV2;
  while( 1 ){
    expRV2=-log(GetDouble());
    expRV-=(expRV2-1)*(expRV2-1)/2;
    if( expRV>0 ) break;  
    expRV=-log(GetDouble());
  }
  if(P(0.5)) {
    return expRV2;
  } else {
    return -expRV2;
  }
}

unsigned int RandomNumberGenerator::GetRandPoisson(const double mean){
  // Draw from a Poisson Dist with mean
  // if cannot calculate, returns UINT_MAX
  // Uses Rejection Method
  unsigned int k=0;
  double a=exp(-mean);
  double u=GetDouble();
  if(a <=0) {
    return UINT_MAX; // cannot calculate, so return UINT_MAX
  }
  while( u>=a ){
    u*=GetDouble();
    ++k;
  }

  return k;
}

unsigned int RandomNumberGenerator::GetFullRandBinomial(const double n, 
							const double p){
  // Actually try n Bernoulli events with probability p
  unsigned int k=0;
  for(unsigned int i=0; i<n; ++i) {
    if(P(p)) {
      k++;
    }
  }
  return k;
}

unsigned int RandomNumberGenerator::GetRandBinomial(const double n, 
						    const double p){
  // Approximate Binomial if appropriate
  // if np(1-p) is large, use a Normal approx
  if(n*p*(1-p) >= _BINOMIAL_TO_NORMAL){
    return (unsigned int)(GetRandNormal(n*p,n*p*(1-p))+0.5);
  }
  // elseif n is large, use a Poisson approx
  if(n >= _BINOMIAL_TO_POISSON){
    unsigned int k=GetRandPoisson(n,p);
    if(k < UINT_MAX) {// if approx worked
      return k;
    }
  }
  // otherwise, actually generate the randBinomial
  return GetFullRandBinomial(n,p);
}


bool RandomNumberGenerator::Choose(unsigned int num_in, 
				   vector<unsigned int> &out_array) {
  // If you ask for more than you pass in...
  assert(num_in >= out_array.size());

  if(num_in == out_array.size()) {
    // init array to 0's
    for(unsigned int i=0; i<out_array.size(); i++) {
      out_array[i] = i;
    }
    return true;
  }

  unsigned int choice_num = 0;
  // @CAO this could be done a lot faster when choose size is close to
  // full size.  However we need to remember to watch out for larger num_in
  while(choice_num < out_array.size()) {
    unsigned int next = GetUInt(num_in);

    // See if this choice is ok to use...
    bool ok = true;
    for(unsigned int i=0; i<choice_num; i++) {
      if(out_array[i] == next) {
	ok = false;
	break;
      }
    }

    // And if its good, record it.
    if(ok == true) {
      out_array[choice_num] = next;
      choice_num++;
    }
  }

  return true;
}

const vector<int> &RandomNumberGenerator::DumpState(void) {
  d_state.clear();
  d_state.push_back(seed);
  d_state.push_back(original_seed);
  d_state.push_back(inext);
  d_state.push_back(inextp);
  for(int i=0; i<56; i++) {
    d_state.push_back(ma[i]);
  }

  return d_state;
}

bool RandomNumberGenerator::LoadState(const vector<int> &state) {
  if(state.size() != 60) {
    return false;
  }

  int count = 0;
  vector<int>::const_iterator it;
  for(it = state.begin(); it != state.end(); ++it) {
    if(*it == -1) {
      count++;
    }
  }

  if(count == 60) {
    ResetSeed(-1);
    return true;
  }

  seed = state[0];
  original_seed = state[1];
  inext = state[2];
  inextp = state[3];
  for(int i=0; i<56; i++) {
    ma[i] = state[4+i];
  }

  return true;
}
