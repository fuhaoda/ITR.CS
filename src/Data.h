#ifndef __DATA_H__
#define __DATA_H__

#include <string>
#include <fstream>
#include <vector>
#include <set> 

namespace ITR {
  
class Data {
public:
  // Constructor
  Data(std::string input);

  // Return the number of sample size 
  int nSample() const { return nSample_; } 

  // Return the number of continuous covariates
  int nCont() const { return nCont_; }

  // Return the number of ordinal covariates
  int nOrd() const { return nOrd_; }

  // Return the number of nominal covariates
  int nNom() const { return nNom_; }

  // Return the total number of covariates
  int nVar() const { return nVar_; }

  // Return the number of actions
  int nAct() const { return nAct_; }

  // Return the number of responses
  int nResp() const { return nResp_; }

  // Return row i, column j of the response matrix
  double resp(int i, int j) const { return resp_[i * nResp_ + j]; }

  // Return row i, column j of the action matrix
  int act(int i, int j) const { return act_[i * nAct_ + j]; } 

  // Return row i, column j of the covariate matrix
  int cvar(int i, int j) const { return cvar_[i * nVar_ + j]; } 

  // Return the number of cuts for variable i
  int nCut(int i) const;

  // Return if component i of variable j belongs to cut k
  bool inCut(int i, int j, int k) const; 
  
private:
  // This function loads the input file. It assumes that fields of the same type
  // are in consecutive columns. It also assumes that the fields are given in
  // the order of subjectID, continuous variable, ordinal variable, nominal
  // variable, action, and responses. 
  void loadCSV(std::string input); 

  // This function parses the header of the input file. It counts the number of
  // continuous, ordinal, and nominal variables, the number of differnet types
  // of actions and responses. 
  void parseCSVHeader(std::ifstream &infile); 

  // This function reads the raw data of the input file. Covariates are read
  // into temporary buffer while actions and responses are read into the
  // internal buffer directly. For ordinal and nominal variables, this function
  // also collects the unique values. 
  void loadRawData(std::ifstream &infile,
                   std::vector<std::vector<double>> &cont,
                   std::vector<std::vector<int>> &ord,
                   std::vector<std::vector<int>> &nom); 

  // This function parses the raw data of the covariates into the format needed
  // by the SearchEngine. Values of the continuous variables are converted into
  // deciles. Values of the ordinal and nominal variables are converted into the
  // order they appear in the unique sets. Variables corresponding to the same
  // sample will be stored contiguously at the end of this function.
  void parseRawData(std::vector<std::vector<double>> &cont,
                    std::vector<std::vector<int>> &ord,
                    std::vector<std::vector<int>> &nom); 

  int nSample_ = 0; // Sample size
  int nCont_ = 0;   // # of continuous variables
  int nOrd_ = 0;    // # of ordinal variables
  int nNom_ = 0;    // # of nominal variables
  int nVar_ = 0;    // # of variables 
  int nAct_ = 0;    // # of different actions
  int nResp_ = 0;   // # of differnet responses 

  std::vector<std::set<int>> uniqOrd_; // unique values of each ordinal variable
  std::vector<std::set<int>> uniqNom_; // unique values of each nominal variable 
  
  // Array of subject ID
  std::vector<int> id_; 
  
  // Response matrix Y[nSample_][nResp_]
  std::vector<double> resp_; 
  
  // Action matrix A[nSample_][nAct_];
  std::vector<int> act_; 

  // Covariate matrix X[nSample_][nCont_ + nOrd_ + nNom_]
  std::vector<int> cvar_;
};


} // namespace ITR

#endif 


