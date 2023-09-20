#include <iostream>
#include <string>
#include <fstream>


using namespace std;


struct Employee {
  string name;
  int nKeysPossessed;
  string keys[5];
};

bool reader(string input_filename, Employee employees[], int& nEmployees) {
  ifstream fin;
  fin.open(input_filename);

  if (!fin.is_open()) {
    return false;
  }
  else {
    fin >> nEmployees;
    fin.ignore();
    
    for (int i = 0; i < nEmployees; ++i) {
      getline(fin, employees[i].name);
      fin >> employees[i].nKeysPossessed;
      for (int x = 0; x < employees[i].nKeysPossessed; ++x) {
        fin >> employees[i].keys[x];
      }
      
      fin.ignore();
    }
    
    fin.close();
    return true;
  }  
}

void writer(string output_filename, Employee employees[], int nEmployees) {
  ofstream fout;
  

  fout.open(output_filename);

  if (!fout.is_open()) {
    cout << "Error outfile not opened!" << endl;
    exit(1);
  }
  
  fout << nEmployees << endl;

  for (int i = 0; i < nEmployees; ++i) {
    fout << employees[i].name << endl;
    fout << employees[i].nKeysPossessed;
    
    for (int j = 0; j < employees[i].nKeysPossessed; ++j) {
      
      fout << " " << employees[i].keys[j];

      if (j == (employees[i].nKeysPossessed - 1)) {
        fout << endl;
      }
      
    }
    
  } 
  fout.close();
}

bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey) {

  for (int i = 0; i < nEmployees; ++i) {
    if ((employees[i].name == emp_name)) {

      
      if (employees[i].nKeysPossessed == 5) {
        cout << "This employee already has 5 keys!" << endl;
        return false;
      }

      
      for (int j = 0; j < employees[i].nKeysPossessed; ++j) {
        if (employees[i].keys[j] == newKey) {
          cout << "This employee already has this key!" << endl;
          return false;
        }
      }
      
      int sum = 0;
      
      for (int k = 0; k < employees[i].nKeysPossessed; ++k) {
        sum = sum + 1;
      }

      employees[i].keys[sum] = newKey;
      employees[i].nKeysPossessed =  employees[i].nKeysPossessed + 1;
      return true;
      
    }
  }

  cout << "Cannot find the specified employee!" << endl;
  return false;
}

bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey) {
  
  for (int i = 0; i < nEmployees; ++i) { // Looping over every element in the employees[] array.

    if (emp_name == employees[i].name) { // If the employee name matches the name we are looking for.
   
      for (int j = 0; j < employees[i].nKeysPossessed; ++j) { // If it is then we loop over the employees.keys inner array.
        
        if ((returnKey == employees[i].keys[j])) { // If we find the matching key, then we are going to remove it

          for (int k = j; k < employees[i].nKeysPossessed; ++k) {
            employees[i].keys[k] = employees[i].keys[k + 1];
          }
          
          employees[i].nKeysPossessed = employees[i].nKeysPossessed - 1;
          return true;      
        }
      }
     
    cout << "This employee does not have the specified key!" << endl;
    return false;
    
    }
       
  }

  cout << "Cannot find the specified employee!" << endl;
  return false;
}

int main() {
  
  string filename;
  int nEmployees;
  Employee employees[10];
  
  

  cout << "Please enter key file name to start: ";
  cin >> filename;
  


  if (reader(filename, employees, nEmployees) == true) {
    int optionNum = 0;
    
    while (optionNum != 7) {
      cout << "Please select from the following options: " << endl;
      cout << "  1. show all employees and their keys" << endl;
      cout << "  2. show the keys an employee possesses" << endl;
      cout << "  3. show which employees possess a specific key" << endl;
      cout << "  4. add a key to an employee" << endl;
      cout << "  5. return a key by an employee" << endl;
      cout << "  6. save the current key status" << endl;
      cout << "  7. exit the program" << endl;

      cin >> optionNum;

      if (optionNum == 1) {
        
        for (int i = 0; i < nEmployees; ++i) {
          cout << "Name: " << employees[i].name << endl;
          cout << "Keys possessed: ";
          
          for (int j = 0; j < employees[i].nKeysPossessed; ++j) { // Goes through keys and prints them.       
            
            cout << employees[i].keys[j] << " ";
            
          }
          cout << endl;
          
        }
        cout << endl;
        
      }

      else if (optionNum == 2) {
        string empname = "";
        cout << "Please enter employee's name: ";
        cin.ignore();
        getline(cin, empname);
        int unmatches = 0;

        for (int i = 0; i < nEmployees; ++i) { // Goes through employee array to find matching name.
          if (empname == employees[i].name) {
            cout << employees[i].name << " possess the following keys: ";
            for (int j = 0; j < employees[i].nKeysPossessed; ++j) { // Goes through that employees keys and prints them.
              
              cout << employees[i].keys[j] << " ";
       
            }
            cout << endl;
            
          }
            
          else {
            unmatches = unmatches + 1;
          }
          
        }

        if (unmatches == nEmployees) {
          cout << "Cannot find the specified employee!" << endl;
        }

        cout << endl;
        

      }

      else if (optionNum == 3) {
        cout << "Please enter a key: ";
        string inputKey;
        cin >> inputKey;
        string names[nEmployees];

        int count = 0;
        
        for (int i = 0; i < nEmployees; ++i) { // Goes through employees.
          for (int j = 0; j < employees[i].nKeysPossessed; ++j) { // Goes through that employees keys.
            if (inputKey == employees[i].keys[j]) { // If match is found, then it adds it to the names array, and count gets one added to it each time a match is found.
              names[count] = employees[i].name;
              count = count + 1;
            }
          }
        }

        if (count == 0) {
          cout << "No one possesses this key." << endl;
        }

        else {
          for (int i = 0; i < count; ++i) {
            cout << names[i] << ", ";
          }

          cout << "possess this key." << endl;
          
        }

        cout << endl;

        
      }

      else if (optionNum == 4) {
        cout << "Please enter employee's name: ";
        string empName;
        cin.ignore();
        getline(cin,empName);
        cout << "Please enter a new key: ";
        string inputKey;
        cin >> inputKey;

        if (addKeyForEmployee(employees,nEmployees, empName, inputKey) == true) {
          cout << "Key added successfully." << endl;
        }
        cout << endl;

      }

      else if (optionNum == 5) {
        cout << "Please enter employee's name: ";
        string empName;
        cin.ignore();
        getline(cin,empName);
        cout << "Please enter the returned key: ";
        string inputKey;
        cin >> inputKey;


        if (returnAKey(employees, nEmployees, empName, inputKey) == true) {
          cout << "Key returned successfully." << endl;
        }
        cout << endl;

      }

      else if (optionNum == 6) {
        cout << "Please enter output file name: " << endl;
        string foutName;
        cin >> foutName;
        writer(foutName, employees, nEmployees);
      }

      else if (optionNum == 7) {
        string foutName = "keys_updated.txt";
        writer(foutName, employees, nEmployees);
        cout << "Thank you for using the system! Goodbye!" << endl;
      }

      else {
        cout << "Not a valid option. Please try again." << endl;
        cout << endl;
        //cin >> optionNum;
      }
      
    }
  }

  else if (reader(filename, employees, nEmployees) == false) {
    cout << "File not found, exiting the program..." << endl;
  }



  
  return 0;
}


