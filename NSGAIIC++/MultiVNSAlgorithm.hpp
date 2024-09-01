#include<vector> 
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <math.h>  
#include <algorithm>
#include "Solution.hpp"

   struct MultiVNSAlgorithm{

    int NbVariable;
    int NbConstraints;
    int NbObjectives; 
    int IndCandidat;
    int NbPop;
    int Nbind; 


    /* Price function */
    std::vector<int> * Price;
    /* Utility function */

    /*Matrix of constraint*/
    std::vector<float>*CostMatrix;
    /*Vector of solution*/





    std::vector<float> * constraint;
    std::vector<Solution> * Non_dominated_Set; 
    std::vector<Solution> * Neighboorhood_Set; 
    Solution IdealPoint; 
    Solution NadirPoint; 




 
    MultiVNSAlgorithm(std::string name){

        int k = 0;
        int number;
        int candidat; 
        Non_dominated_Set = new std::vector<Solution>;
        Neighboorhood_Set = new std::vector<Solution>; 
        

            std::ifstream fichier(name);
                if(fichier){

                   

                     fichier >> NbVariable;
                     fichier >> NbObjectives;
                     fichier >> NbConstraints; 

                     std::cout << "Les caractéristiques du problèmes sont: " << std::endl;
                     std::cout << "Le nombre d'objectifs est: " << NbObjectives << std::endl;
                     std::cout << "Le nombre de contraintes est: " << NbConstraints << std::endl;


             


                     Price = new std::vector<int>[NbObjectives]; 
                     CostMatrix = new std::vector<float>[NbConstraints];
                     constraint = new std::vector<float>[NbConstraints]; 


                     


                   for (int i = 0; i < NbObjectives; i++){
                     while(k < NbVariable){
                        fichier >> number; 
                        Price[i].push_back(number);
                        k++;
                        };
                        k = 0;
                   }


                     for(int i = 0; i < NbConstraints; i++){
                        k = 0;

                        while(k < NbVariable){
                            fichier >> number; 
                            CostMatrix[i].push_back(number);
                            k++;
                        }
                     }


              
                        for(int i = 0; i < NbConstraints; i++){
                        fichier >> number;
                        std::cout << "la contrainte est: " << number << std::endl;
                        constraint[i].push_back(number);

                     } 
                     
                }
    }




 

    
    void sumconstraint(Solution & individual){
        float addconstraint;
        for(int j = 0;j < NbConstraints; j++){
            addconstraint = 0;
            for(int i = 0; i < NbVariable; i++){
               addconstraint += CostMatrix[j][i] * individual.solution[0][i];


            }
            individual.SumConstraint->push_back(addconstraint);
                std::cout <<  individual.SumConstraint[0][j] << std::endl;  
        }
    }

    void checkindividual(Solution & individual){
        bool check = true;

        for(int i = 0; i < NbConstraints; i++){
            std::cout << "La contrainte est: " << constraint[i][0] << std::endl;
            if( individual.SumConstraint[0][i] > constraint[i][0] || individual.SumConstraint[0][i] == 0){
             
                check = false;
                break;
            }
        }

        std::cout << "le booléen est: " << check << std::endl;

        if(check == false){
            std::cout << "La solution n'est pas admissible" << std::endl; 

        }else{

        std::cout << "La solution est admissible" << std::endl; 
        Non_dominated_Set->push_back(individual);

        }
   


        }
        

    

    


    void initnondominatedSet(){
        int nbrandomseeds;
        int indice; 
        int value;
        while(Non_dominated_Set[0].size() > 0){
        Solution individual;
            for(int k = 0; k < NbVariable; k++){
                 individual.solution->push_back(0);
            }
            nbrandomseeds = rand() %  NbVariable;
            std::cout << nbrandomseeds << std::endl;  
            for(int j = 0; j < nbrandomseeds; j++){
                indice = rand() % NbVariable ;
                value = rand() % 2;
                if(value > 0){

                  individual.solution[0][indice] = 1; 


                }

            }
            sumconstraint( individual);
            individual.computeFitessValue(Price,NbVariable);
            individual.displayIndividual(NbVariable, NbConstraints);

            checkindividual(individual);
    }
    }

    }


    void displaynondominatedSet(){

        sort(Non_dominated_Set[0].begin(), Non_dominated_Set[0].end(),RangeRankSolution());

        std::cout << "La population est: " << std::endl; 
        for(int i = 0;i < NbPop; i++){
            std::cout << "individu_" << i + 1 << " : ";
            for(int j = 0; j < NbVariable; j++){

                std::cout << Population[0][i].solution[0][j] << " ";
            }

            std::cout << "obj1: " << Population[0][i].FitnessValue1 << " " << "obj2: " << Population[0][i].FitnessValue2 << " rank: " << Population[0][i].rank <<   std::endl;  



        }

      

    }

    void displayList(std::vector<Solution> & List){

        std::cout << "La Liste est: " << std::endl; 
        for(int i = 0;i < List.size(); i++){
            std::cout << "individu_" << i + 1 << " : ";
            for(int j = 0; j < NbVariable; j++){

                std::cout << List[i].solution[0][j] << " ";
            }

            std::cout << "obj1: " << List[i].FitnessValue1 << " " << "obj2: " << List[i].FitnessValue2 << " rank: " << List[i].rank <<   std::endl;  



        }

      

    }


   void displayEchantillon(){
        std::cout << "L'Echantillon est: " << std::endl; 
        for(int i = 0;i < Nbind; i++){
            std::cout << "individu_" << i + 1 << " : ";
            for(int j = 0; j < NbVariable; j++){

                std::cout << Echantillon[0][i].solution[0][j] << " ";
            }

            std::cout << "obj1: " << Echantillon[0][i].FitnessValue1 << " " << "obj2: " << Echantillon[0][i].FitnessValue2 << std::endl;  




        }
      }
                
                



    

    void displayCostMatrix(){
        for(int i = 0; i < NbConstraints; i++){
            for(int j = 0; j < NbVariable; j++)
            {
                std::cout << CostMatrix[i][j] << " ";

        }

        std::cout << std::endl;
        }
    }


    void displayProblemVega(){



       std::cout << "Les prix des fonctions objectifs sont: " << std::endl;
       for(int i = 0; i < NbObjectives; i++){
        for(int j = 0; j <NbVariable; j++){
            std::cout << Price[i][j] << " ";
        }
        std::cout << std::endl;
       }

        std::cout << "La matrice des contraintes est: " << std::endl; 
             for(int i = 0; i < NbConstraints; i++){
            for(int j = 0; j < NbVariable; j++)
            {
                std::cout << CostMatrix[i][j] << " ";

        }

        std::cout << std::endl;
        }

        std::cout << "Les contraintes sont:";
        for(int i = 0; i < NbConstraints; i++){
            std::cout << constraint[i][0] << std::endl;
        }

    }


    void fitnessValuePop(/*std::vector<Solution> & Echantillon, int dim*/){
        float fitnessvalue1;
        float fitnessvalue2; 
        int compteur = 0;
        while(compteur < NbPop)
        {
            fitnessvalue1 = 0; 
            fitnessvalue2 = 0;
            if(Population[0][compteur].fitnessCalculated == false){
                for(int i = 0; i < NbVariable; i++){
                    fitnessvalue1+= Population[0][compteur].solution[0][i] * Price[0][i];
                    fitnessvalue2+= Population[0][compteur].solution[0][i] * Price[1][i];

                }
                Population[0][compteur].FitnessValue1 = fitnessvalue1;
                Population[0][compteur].FitnessValue2 = fitnessvalue2; 
 
                Population[0][compteur].fitnessCalculated = true;
            }

            compteur++;


        }
    }


    void rankPopulation(){
        int compteur = 0;     
        int nextrank = 0; 
        int Nbrank = 0;
        int indMax = 0;
        bool ranked; 
        float max; 
        sort(Population[0].begin(), Population[0].end(),Solution());
        for(int k = 0; k < NbPop; k++){
            Population[0][k].rank = NbPop + 1;
        }

        while(Nbrank < NbPop){
            ranked = false; 
            max = Population[0][compteur].FitnessValue2;
            Population[0][compteur].rank = nextrank; 
            for(int k = compteur; k < NbPop ; k++){
                if(Population[0][k].FitnessValue2 < max ){
                    if(ranked == false){
                    compteur = k;
                    ranked = true;
                    } 
                    }
                    else{
          
                        if(Population[0][k].checkrank == false){
                        Population[0][k].rank = nextrank;
                        max = Population[0][k].FitnessValue2;
                        indMax = k;
                        Population[0][k].checkrank = true;
                        Nbrank ++; 
                        
                    }
                }
            }

            nextrank++;

        }
    }


                                   


        
    

    void fitnessValueSample(){
        float fitnessvalue1;
        float fitnessvalue2; 
        int compteur = 0;
        while(compteur < Nbind)
        {
            fitnessvalue1 = 0; 
            fitnessvalue2 = 0; 
            if(Echantillon[0][compteur].fitnessCalculated == false){
                for(int i = 0; i < NbVariable; i++){
                    fitnessvalue1 += Echantillon[0][compteur].solution[0][i] * Price[0][i];
                    fitnessvalue2 += Echantillon[0][compteur].solution[0][i] * Price[1][i]; 
                }
                Echantillon[0][compteur].FitnessValue1 = fitnessvalue1;
                Echantillon[0][compteur].FitnessValue2 = fitnessvalue2;
                Echantillon[0][compteur].fitnessCalculated = true;
            }

            compteur++;


        }


    }

   



    void CheckSampleindividual(Solution & individual){
        bool check = true;
        for(int i = 0; i < NbConstraints; i++){
            std::cout << "La contrainte est: " << constraint[i][0] << std::endl;
            if( individual.SumConstraint[0][i] > constraint[i][0] || individual.SumConstraint[0][i] == 0){
             
                check = false;
                break;
            }
        }
        std::cout << "le booléen est: " << check << std::endl;
        if(check == false){
            std::cout << "La solution n'est pas admissible" << std::endl; 
        
            if(compteur < 1){
                RepaireSample(individual);
                compteur++;
                CheckSampleindividual(individual, compteur, ind);

            }
            }else{
                std::cout << "La solution est admissible" << std::endl; 
                Echantillon[0][ind] = individual;
                compteur++;
                }
            }




    }






//movement 
//drop 
   void drop(){
        int compteur = 0;
        int nb_one = 0;
        int indice;
        int choix; 
        

        for(int i = 0; i < NbVariable; i++){
            if(NeighbourSolution[0][i] > 0){
            nb_one++;  
            }
        }
        int listChoix[nb_one];
        for(int i = 0; i < NbVariable; i++){
            if(NeighbourSolution[0][i] > 0){
                listChoix[compteur] = i;
                compteur++;
            }
        }

        indice = rand() % compteur;
        std::cout << "indice à supprimer: " << indice << std::endl;
        choix = listChoix[indice];
        NeighbourSolution[0][choix] = 0;

    }

//add 
    void add(){
        int compteur = 0;
        int nb_one = 0;
        int indice;
        int choix; 
        

        for(int i = 0; i < NbVariable; i++){
            if(NeighbourSolution[0][i] < 1){
            nb_one++;  
            }
        }
        int listChoix[nb_one];
        for(int i = 0; i < NbVariable; i++){
            if(NeighbourSolution[0][i] < 1){
                listChoix[compteur] = i;
                compteur++;
            }
        }

        indice = rand() % compteur;
        choix = listChoix[indice];
        NeighbourSolution[0][choix] = 1;



    }



//repaire 

    void Repaire(Solution & Enfant){
        int compteur = 0;
        int nb_one = 0;
        int indice;
        int choix; 
        

        for(int i = 0; i < NbVariable; i++){
            if(Enfant.solution[0][i] > 0){
            nb_one++;  
            }
        }
        int listChoix[nb_one];
        for(int i = 0; i < NbVariable; i++){
            if(Enfant.solution[0][i] > 0){
                listChoix[compteur] = i;
                compteur++;
            }
        }

        indice = rand() % compteur;
        std::cout << "indice à supprimer: " << indice << std::endl;
        choix = listChoix[indice];
        Enfant.solution[0][choix] = 0;

    }




 

//Update by rank and crowding distance 

   void Update(){
    int compteur = 0; 
    int indicefront = 0;
    bool Update = false;
    int indiceVec = 0;
    int comptList = 0; 
    int nbListInd = NbPop + Nbind;
    fitnessValueSample();
    std::vector<Solution> List;
    for(int i = 0; i < NbPop; i++){
        List.push_back(Population[0][i]);
    }
    for(int j = 0; j < Nbind; j++){
        List.push_back(Echantillon[0][j]);
    }

    while(compteur < NbPop){
    sort(Front[0][indicefront].begin(), Front[0][indicefront].end(),RangeRankcrowdingMeasure());
    for(int k = 0; k < Front[0][indicefront].size();k++){
        Population[0][compteur] = Front[0][indicefront][k];
        compteur++;
        if(compteur > NbPop - 1){
            std::cout << "La génération suivante est créee" << std::endl;
            break;
        }
    }
    indicefront++;
}
}

//void resolve(int Nbgen){ 
//int nbCrossover;
//displayProblemVega();
//computeExtremePoint();
//initPopulation();
//displayPopulation();
//   fitnessValuePop();
//   rankPopulation();
//  displayPopulation();
  

  // }




