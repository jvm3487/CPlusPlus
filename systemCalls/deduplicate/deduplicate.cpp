#include <cstdlib>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

class HashElement{
 private:
  std::string fileLocation;
  std::string mdFive;
  HashElement * next;
  HashElement * previous;
  bool alreadyDelete;
  bool doNotDelete;
 public:
  ~HashElement(){
    delete next;
  }
  HashElement(): fileLocation(std::string()), mdFive(std::string()), next(NULL), previous(NULL), alreadyDelete(false), doNotDelete(false){}
  HashElement(std::string loc, std::string md): fileLocation(loc), mdFive(md), next(NULL), previous(NULL), alreadyDelete(false), doNotDelete(false){
    mdFive.resize(32);
  }
  friend class Hash;
};

class Hash{
 private:
  HashElement ** hashArray;
  int numElements;
 public:
  ~Hash(){
    for(int i = 0 ; i < numElements; i++){
      delete hashArray[i];
    }
    delete[] hashArray;
  }
  Hash(){
    hashArray = new HashElement*[16];
    numElements = 16;
    for(int i = 0; i < numElements; i++){
      hashArray[i] = NULL;
    }
  }
  void addElement(HashElement & rhs){
    int index = 0;
    switch(rhs.mdFive.at(0)){
    case '0': index = 0; break;
    case '1': index = 1; break;
    case '2': index = 2; break;
    case '3': index = 3; break;
    case '4': index = 4; break;
    case '5': index = 5; break;
    case '6': index = 6; break;
    case '7': index = 7; break;
    case '8': index = 8; break;
    case '9': index = 9; break;
    case 'a': index = 10; break;
    case 'b': index = 11; break;
    case 'c': index = 12; break;
    case 'd': index = 13; break;
    case 'e': index = 14; break;
    case 'f': index = 15; break;  
    default: index = 16; break;
    }
    if (hashArray[index] == NULL){
      hashArray[index] = &rhs;
    } 
    else{
      HashElement * temp = hashArray[index];
      while(temp->next != NULL){
	if (rhs.fileLocation != temp->fileLocation){
	  temp = temp->next;
	}
	else{
	  delete &rhs;
	  return;
	}
      }
      if (rhs.fileLocation == temp->fileLocation){
	delete &rhs;
	return;
      }
      temp->next = &rhs;
      temp->next->previous = hashArray[index];
    }
  }
  void compareAndPrint(FILE * output){
    for (int i = 0; i < numElements; i++){
      HashElement * temp = hashArray[i];
      if (temp != NULL){
	while (temp->next != NULL){
	  HashElement * temp2 = temp->next;
	  while (temp2 != NULL){
	    std::string commandToRun = "diff ";
	    commandToRun.append(temp->fileLocation);
	    commandToRun.append(" ");
	    commandToRun.append(temp2->fileLocation);
	    FILE * f = NULL;
	    //std::cout << "I'm here" <<std::endl;
	    char * line = NULL;
	    size_t size= 0;
	    if (temp2->fileLocation != temp->fileLocation){
	      f = popen(commandToRun.c_str(), "r");
	      if (getline(&line,&size,f) == -1){
		if (temp2->alreadyDelete != true && temp2->doNotDelete != true){
		  fprintf(output, "#Removing %s (duplicate of %s).\n", temp2->fileLocation.c_str(), temp->fileLocation.c_str());
		  fprintf(output, "rm %s\n", temp2->fileLocation.c_str());
		  temp2->alreadyDelete = true;
		  temp->doNotDelete = true;
		}
	      }
	      free(line);
	    }
	    fclose(f);
	    temp2 = temp2->next;
	  }
	  temp = temp->next;
	}
      }
    }
  }
};

FILE * findFilesInDirectory(char * dirName){
  std::string commandToRun = "find ";
  commandToRun.append(dirName);
  /* -not  -iwholename '*.svn*' */
  commandToRun.append(" -type f ! -name '*svn*' ! -wholename */.svn/entries*");
  return popen(commandToRun.c_str(), "r");
}

void storeInHash(char * line, Hash * fileHash){
  std::string command = "md5sum ";
  command.append(line);
  FILE * f = popen(command.c_str(), "r");
  size_t bytes = 0;
  char * line2 = NULL;
  while (getline(&line2, &bytes, f) != EOF){
    HashElement * temp = new HashElement(line,line2);
    //std::cout <<line2<<std::endl;
    fileHash->addElement(*temp);
  }
  fclose(f);
  free(line2);
}

int main(int argc, char ** argv){
  if (argc < 2){
    fprintf(stderr, "Usage: One or more directories\n");
    exit (EXIT_FAILURE);
  }
  Hash * fileHash = new Hash;
  for (int i = 0; i < argc-1; i++){
    FILE * fileList = findFilesInDirectory(argv[i+1]);
    size_t bytes = 0;
    char * line = NULL;
    while(getline(&line, &bytes, fileList) != EOF){
      line[strlen(line)-1] = '\0';
      char * line3 = NULL;
      size_t size = 0;
      std::string johnCommand = "readlink -f ";
      johnCommand.append(line);
      FILE * g = popen(johnCommand.c_str(), "r");
      //std::cout << line << std::endl;
      getline(&line3,&size,g);
      line3[strlen(line3)-1] = '\0';
      //std::cout << line3 << std::endl;
      storeInHash(line3, fileHash);
      //std::cout << "Im here 4" <<std::endl;
      free(line3);
      fclose(g);
    }
    free(line);
    fclose(fileList);
  }
  FILE * output = fopen("deduplicate.sh", "w");
  fprintf(output, "#!/bin/bash\n");
  fileHash->compareAndPrint(output);
  fclose(output);
  fprintf(stdout, "finish generating shell script\n");
  delete fileHash;
  return EXIT_SUCCESS;
}
