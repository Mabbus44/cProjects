#include "Day21.h"
#include <map>
#include <algorithm>

void Recepie::load(vector<string> input){
  bool loadingAllergens = false;
  for(string s:input){
    if(loadingAllergens)
      allergens.push_back(s);
    if(s.compare("(contains") == 0)
      loadingAllergens = true;
    if(!loadingAllergens)
      ingredients.push_back(s);
  }
}

void Recepie::output(){
  for(string ingridient: ingredients)
    cout << " " << ingridient;
  cout << " (contains ";
  for(string allergen: allergens)
    cout << " ," << allergen;
  cout << ")" << endl;
}

Day21::Day21()
{
  //ctor
}

Day21::~Day21()
{
  //dtor
}

void Day21::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({" ", ",", ")"});
  vector<Recepie> recepies;
  for(vector<string> vs: vvs)
    recepies.push_back(Recepie(vs));

  map<string, vector<string>> mayContain;
  map<string, int> allAllergens;
  vector<string> allAllergensVector;
  for(Recepie& r:recepies){
    for(string allergen:r.allergens){
      allAllergens[allergen] = 0;
    }
  }
  for(map<string, int>::iterator a=allAllergens.begin(); a!=allAllergens.end(); a++){
    allAllergensVector.push_back(a->first);
  }
  for(Recepie& r:recepies){
    for(string ingredient:r.ingredients){
      mayContain[ingredient] = allAllergensVector;
    }
  }
  for(map<string, vector<string>>::iterator mayContainIt=mayContain.begin(); mayContainIt!=mayContain.end(); mayContainIt++){
    for(string allergen: allAllergensVector){
      bool allergenPossible=true;
      int recepieId=0;
      for(vector<Recepie>::iterator recepieIt = recepies.begin(); recepieIt != recepies.end() && allergenPossible; recepieIt++){
        if(find(recepieIt->ingredients.begin(), recepieIt->ingredients.end(), mayContainIt->first) == recepieIt->ingredients.end() &&
           find(recepieIt->allergens.begin(), recepieIt->allergens.end(), allergen) != recepieIt->allergens.end()){
          allergenPossible = false;
        }
        recepieId++;
      }
      if(!allergenPossible){
        mayContainIt->second.erase(remove(mayContainIt->second.begin(), mayContainIt->second.end(), allergen), mayContainIt->second.end());
      }
    }
  }
  int recepieCount=0;
  for(map<string, vector<string>>::iterator mayContainIt=mayContain.begin(); mayContainIt!=mayContain.end(); mayContainIt++){
    if(mayContainIt->second.size() == 0){
      for(vector<Recepie>::iterator recepieIt = recepies.begin(); recepieIt != recepies.end(); recepieIt++){
        if(find(recepieIt->ingredients.begin(), recepieIt->ingredients.end(), mayContainIt->first) != recepieIt->ingredients.end())
          recepieCount++;
      }
    }
  }
  cout << "part 1: " << recepieCount << endl;
}

void Day21::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs = loader.toVectorStr2d({" ", ",", ")"});
  vector<Recepie> recepies;
  for(vector<string> vs: vvs)
    recepies.push_back(Recepie(vs));

  map<string, vector<string>> mayContain;
  map<string, int> allAllergens;
  vector<string> allAllergensVector;
  for(Recepie& r:recepies){
    for(string allergen:r.allergens){
      allAllergens[allergen] = 0;
    }
  }
  for(map<string, int>::iterator a=allAllergens.begin(); a!=allAllergens.end(); a++){
    allAllergensVector.push_back(a->first);
  }
  for(Recepie& r:recepies){
    for(string ingredient:r.ingredients){
      mayContain[ingredient] = allAllergensVector;
    }
  }
  for(map<string, vector<string>>::iterator mayContainIt=mayContain.begin(); mayContainIt!=mayContain.end(); mayContainIt++){
    for(string allergen: allAllergensVector){
      bool allergenPossible=true;
      int recepieId=0;
      for(vector<Recepie>::iterator recepieIt = recepies.begin(); recepieIt != recepies.end() && allergenPossible; recepieIt++){
        if(find(recepieIt->ingredients.begin(), recepieIt->ingredients.end(), mayContainIt->first) == recepieIt->ingredients.end() &&
           find(recepieIt->allergens.begin(), recepieIt->allergens.end(), allergen) != recepieIt->allergens.end()){
          allergenPossible = false;
        }
        recepieId++;
      }
      if(!allergenPossible){
        mayContainIt->second.erase(remove(mayContainIt->second.begin(), mayContainIt->second.end(), allergen), mayContainIt->second.end());
      }
    }
  }
  map<string, vector<string>> doesContain;
  for(map<string, vector<string>>::iterator mayContainIt=mayContain.begin(); mayContainIt!=mayContain.end(); mayContainIt++){
    if(mayContainIt->second.size() > 0){
      doesContain[mayContainIt->first] = mayContainIt->second;
    }
  }
  bool deleted = true;
  while(deleted){
    deleted = false;
    for(map<string, vector<string>>::iterator doesContainIt=doesContain.begin(); doesContainIt!=doesContain.end(); doesContainIt++){
      if(doesContainIt->second.size() == 1){
        for(map<string, vector<string>>::iterator doesContainIt2=doesContain.begin(); doesContainIt2!=doesContain.end(); doesContainIt2++){
          if(doesContainIt2->second.size() > 1 && find(doesContainIt2->second.begin(), doesContainIt2->second.end(), doesContainIt->second[0]) != doesContainIt2->second.end()){
            deleted = true;
            doesContainIt2->second.erase(remove(doesContainIt2->second.begin(), doesContainIt2->second.end(), doesContainIt->second[0]), doesContainIt2->second.end());
          }
        }
      }
    }
  }
  string ingredients[doesContain.size()];
  string allergens[doesContain.size()];
  int i=0;
  for(map<string, vector<string>>::iterator doesContainIt=doesContain.begin(); doesContainIt!=doesContain.end(); doesContainIt++){
    ingredients[i] = doesContainIt->first;
    allergens[i] = doesContainIt->second[0];
    i++;
  }
  bool changed = true;
  while(changed){
    changed = false;
    for(i=0; i<(int)doesContain.size()-1; i++){
      if(allergens[i] > allergens[i+1]){
        swap(allergens[i], allergens[i+1]);
        swap(ingredients[i], ingredients[i+1]);
        changed = true;
      }
    }
  }
  string ans=ingredients[0];
  for(i=0; i<(int)doesContain.size(); i++){
    if(i>0)
      ans = ans + "," + ingredients[i];
  }
  cout << "part 2: " << ans << endl;
}
