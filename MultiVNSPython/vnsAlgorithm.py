import random 
import math 


class Solution: 
  def __init__(self, nbVariable,nbconstraint,listConstraint):
        
        self.solution = [0 for i in range(nbVariable)]
        self.SumConstraint = [0 for i in range(nbconstraint)]
        self.fitnessValue1 = 0
        self.fitnessValue2 = 0 

        self.NbVariable = nbVariable
        self.Nbconstraint = nbconstraint
        self.listConstraint = listConstraint

        self.admissible = False 
        

  def sumconstraint(self, matrix):
       self.SumConstraint = [sum([matrix[ind1][ind2] * self.solution[ind2] for ind2 in range(self.NbVariable)])for ind1 in range(self.Nbconstraint)]
       
  def calculatefitnessvalue(self,Price):
        self.fitnessValue1 = sum([Price[0][i] * self.solution[i] for i in range(self.NbVariable)]) 
        self.fitnessValue2 = sum([Price[1][i] * self.solution[i] for i in range(self.NbVariable)]) 
        
  def CheckIndividual(self):
        check = True
        for k in range(self.Nbconstraint):
              print(self.SumConstraint[k])
              if(self.SumConstraint[k] > self.listConstraint[k] or self.SumConstraint[k] == 0):
                    check = False
                    break
        if check == False:
              print("La solution n'est pas admissible")
              self.admissible = False
        else:
              "La solution est admissible"  
              self.admissible = True


        
  def addmutation(self):
        indlistadd = [i for i in range(self.NbVariable) if self.solution[i] == 0]
        if len(indlistadd) < 1:
              print("Il n'y a rien a muté")
        else:
              indice = random.choice(indlistadd)
              self.solution[indice] = 1
        
  def repaire(self):
        indlistadd = [i for i in range(self.NbVariable) if self.solution[i] == 1]
        indice = random.choice(indlistadd)
        self.solution[indice] = 0
        
  def checkandrepaire(self,compteur):
        check = True
        for k in range(self.Nbconstraint):
              print(self.SumConstraint[k])
              if(self.SumConstraint[k] > self.listConstraint[k] or self.SumConstraint[k] == 0):
                    check = False
                    compteur += 1 
                    if(compteur < 1):
                          self.repaire()
                          self.checkandrepaire(compteur)
                    break
        if check == False:
              print("La solution n'est pas admissible")
              self.admissible = False
        else:
              "La solution est admissible"  
              self.admissible = True
        
        
   
class vnsAlgorithm():
    
  def __init__(self, NbPop,NbInd):
        """Constructeur de notre classe"""
        self.NbVariable = 0 
        self.NbObjectives = 0 
        self.NbConstraint = 0 
        self.PriceVariable = []
        self.Constraint = []
        self.MatrixConstraint = []
        self.point_choosen = 0 
        self.non_dominated_points = []
        self.neighborhood_points = []
        
        
        
  def checknumber(self,lignes,indice):
        ParsedList = []
        compteur1 = 0
        compteur2 = 0
        while(lignes[indice][compteur1] != '\n' and lignes[indice][compteur2] != '\n'):
              while(lignes[indice][compteur2] != " " and lignes[indice][compteur2] != '\n'):
                    compteur2 += 1
              ParsedList.append(int(lignes[indice][compteur1:compteur2]))
              compteur1 = compteur2 + 1
              compteur2 = compteur1

   
              if compteur1 > len(lignes[indice]) - 1:
                    break
        return ParsedList
 
 
  
  def parseKnapsack(self,text):
      fichier = open(text, "r",encoding="utf8")
      lignes = fichier.readlines()
      tab = [self.checknumber(lignes,indice) for indice in range(len(lignes) - 1)]
      self.NbVariable = tab[0][0]
      self.NbObjectives = tab[0][1]
      self.NbConstraint = tab[0][2]
      self.PriceVariable = [[tab[ind2][ind1] for ind1 in range(self.NbVariable)] for ind2 in range(1,self.NbObjectives + 1)]
      self.MatrixConstraint = [[tab[ind][j] for j in range(self.NbVariable)] for ind in range(3,3 + self.NbConstraint )]
      self.constraint = [tab[-1][ind] for ind in range(self.NbConstraint)]
      


      
 
def init_non_dominated_point(self):
      self.non_dominated_points = [Solution(self.NbVariable,self.NbConstraint,self.constraint)]
      for i in range(self.NbPop):
            self.non_dominated_points[i].solution = [random.randrange(0,2) for i in range(self.NbVariable)]
            self.non_dominated_points[i].sumconstraint(self.MatrixConstraint)
            self.non_dominated_points[i].CheckIndividual()
            while(self.non_dominated_points[i].admissible == False):
                  self.non_dominated_points[i].solution = [random.randrange(0,2) for i in range(self.NbVariable)]
                  self.non_dominated_points[i].sumconstraint(self.MatrixConstraint)
                  self.non_dominated_points[i].CheckIndividual()
            self.non_dominated_points[i].calculatefitnessvalue(self.PriceVariable)
            self.point_choosen = init_non_dominated_point[0]
            
             
def add(self):
      list_alea = [i for i in range(self.NbVariable) if self.CopySolution[i] == 0]
      indice = random.choice(list_alea)
      self.CopySolution[indice] = 1
      
def drop(self):
      list_alea = [i for i in range(self.NbVariable) if self.CopySolution[i] == 1]
      indice = random.choice(list_alea)
      self.CopySolution[indice] = 0
      
def neightboorhood(self):
      
            
            

def displayProblem(self):
      print("The number of variable is: " , self.NbVariable)
      print("The number of constraint is: " , self.NbConstraint)
      print("The number of objectives is: " , self.NbObjectives)
      print("The vector of price is: " , self.PriceVariable)
      print("The cost Matrix is: " , self.MatrixConstraint)
      print("The constraints are: ", self.constraint)

        

                  
                   
def display_non_dominated_points(self):
        print("The population is: ")
        for i in range(self.NbPop):
              print(self.non_dominated_points[i].solution, " ", self.non_dominated_points[i].fitnessValue1, self.non_dominated_points[i].fitnessValue2)
              
                      
def displaySample(self):
        print("The sample is: ")
        for i in range(self.NbInd):
              print(self.Sample[i].solution, " ", self.Sample[i].fitnessValue1, self.Sample[i].fitnessValue2, self.Sample[i].rank)

        
         
                    
def define_non_dominated_pointsfront(self):
        self.non_dominated_points.sort(key = lambda x: x.rank)
        numberRank = self.non_dominated_points[-1].rank 
        print("rang",numberRank)
        self.front = [[self.non_dominated_points[i] for i in range(self.NbPop) if self.non_dominated_points[i].rank == r] for r in range(numberRank + 1)]
        print("bonjour",self.front)
        while len(self.front[-1]) < 1:
              self.front = self.front[0:(len(self.front) - 1)]
        
      
        
def Update_non_dominated_points(self):
      compteur = 0 
      max = 0 
      ind_max = 0 
      arret = False 
      list_toupdate = []
      updated_list = []
      self.non_dominated_points.sort(key = lambda x: x.fitnessValue1, reverse = True)
      for i in range(len(self.non_dominated_points)):
            list_toupdate.append(self.non_dominated_points[i])
      for i in range(len(self.neighborhood_points)):
            list_toupdate.append(self.neighborhood_points[i])
      updated_list.append(list_toupdate[0])
      max = list_toupdate[0].fitnessValue2
      ind_max = 0 
      for i in range(1,len(self.List)):
              if  list_toupdate[i].fitnessValue2 > list_toupdate[ind_max].fitnessValue2 and self.List[i].fitnessValue1 <= self.List[i - 1].fitnessValue1: 
                    updated_list.append(list_toupdate[i])
                    max = list_toupdate[i].fitnessValue2 
                    ind_max = i 
      self.non_dominated_points = updated_list
                    
                    
def Update_neighborhood(self):
      compteur = 0 
      max = 0 
      ind_max = 0 
      arret = False 
      list_toupdate = []
      updated_list = []
      self.neighborhood_points.sort(key = lambda x: x.fitnessValue1, reverse = True)
      list_toupdate = []
      updated_list = []
      for i in range(len(self.neighborhood_points)):
            list_toupdate.append(self.neighborhood_points[i])
      updated_list.append(list_toupdate[0])
      max = list_toupdate[0].fitnessValue2
      ind_max = 0 
      for i in range(1,len(self.List)):
              if  list_toupdate[i].fitnessValue2 > list_toupdate[ind_max].fitnessValue2 and self.List[i].fitnessValue1 <= self.List[i - 1].fitnessValue1: 
                    updated_list.append(list_toupdate[i])
                    max = list_toupdate[i].fitnessValue2 
                    ind_max = i 
      self.neighborhood_points = updated_list
                    

                    
            
 


  
        
def resolve(self, Nbgen):
        self.initnon_dominated_points()
        self.computeExtremePoint()
        self.displaynon_dominated_points()
        for i in range(Nbgen):
              self.displaynon_dominated_points()     

              self.ranknon_dominated_points()
              self.displaynon_dominated_points()     

              self.definenon_dominated_pointsfront()
     
              self.measurecrowdingdistance()
              self.tounament()              
              NbMutation = random.randrange(self.NbInd)
              self.displaySample()
              for j in range(NbMutation):
                    self.crossOverMutation()
              self.Updatenon_dominated_points()
        self.displaynon_dominated_points()     



            
              

   




    
      




        


              
              
         
         




        
        
            
      



     

 
    

           
    
    

        
  
        
  
        

      
             
        
             
             
            
             
            



             
            
            

            
             
          
            

        
        
        




     






    
      
        

