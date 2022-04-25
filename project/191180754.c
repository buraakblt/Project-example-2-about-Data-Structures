/*
M�zik listesini olu�turmak amac� ile Dairesel Ba�l� Liste kulland�m. Dairesel Ba�l� listenin normal ba�l� listeden fark� son eleman�n�n bir null'a de�il ilk elemana ba�l� olmas�d�r.
Bu Ba�l� liste Node yap�lar�ndan olu�mu�tur,her bir Node yap�s� gene Node pointeri ile ba�ka bir Node'u g�sterir ve bu �ekilde birbirine ba�l� bir liste yap�s� olu�ur.
Bu yap� ile InsertSong komutu geldik�e bu liste yap�s�n�n ba��na ya da sonuna gelen komuta g�re bir Node eklenmi�tir.MoveSong komutunda ise Node pointerinin g�sterdi�i Node ile oynanarak
Listede Nodelar�n yerlerinde de�i�iklik sa�lanm��t�r.Remove komutunda iste silinmek istenen Node'la olan ba�lant� kopar�lm�� daha sonra bu Node free() fonksiyonu ile silinmi�tir.
ReversePlaylist komutunda recursive bir yap� ile Nodelar�n ba�lar�nda de�i�iklik yap�larak terse d�nd�rme i�lemi sa�lanm��t�r,benzer bir yap� PrinntPlaylist komutunun R parametreli halinde de kullan�lm��t�r.
�ark� isimlerini tutmak i�inse bir char array'i kullan�lm��.Bu array'in boyutu pdfte belirtildi�i gibi en fazla 50 karakter i�in �eklinde ayarlanm��t�r.
Burak Bulut 
Data Structures Final 
191180754
*/
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<stdbool.h>
typedef struct Node { 
   	char Songname[50];
    struct Node* next; 
}Node;
typedef struct Current{
	char Songname[50];
}Current;

void printReverse(Node *head,Node *firstnode,FILE* fout){
	if(head->next==firstnode){
		fprintf(fout,"%s\n",head->Songname);
		return;
	} 
	printReverse(head->next,firstnode,fout);
	fprintf(fout,"%s\n",head->Songname);
	
}

void print(Node *head,char* Order,FILE* fout) {
 struct Node *temp = head; 
 if(head==NULL){
 	fprintf(fout,"No Songs To Print\n*****\n");
 	return;
 }
 if(strcmp(Order,"F")==0){

  
        do
        {
            fprintf(fout,"%s\n", temp->Songname);
            temp = temp->next;
        }
        while (temp != head);
    
   }
   else if(strcmp(Order,"R")==0){
   		printReverse(head,head,fout);
   }
    fprintf(fout,"*****\n");
}

void ReversePlaylist(Node*  prev,Node* curr,Node* currnext,Node *firstnode){
	
	if(curr==firstnode){
		curr->next=prev;
		return;
	}
		ReversePlaylist(curr,currnext,currnext->next,firstnode);
		curr->next=prev;
}

Node Delete(char songname[50],Node *head){

	Node *temp=head;
	if (temp->next == head) { return NULL; }
	while ((strcmp(temp->next->Songname, songname) != 0)) {
		temp = temp->next;
	}
	Node* deleted = temp->next;
	temp->next = temp->next->next;
	free(deleted);
	return temp->next;
}


Current* PlaySong(Node *head,char* Placement,Current *CurrentlyPlaying){
	Node *temp=head;
	if(temp==NULL){
		return CurrentlyPlaying ;
	}
	
	if(strcmp(Placement,"P")==0){	
		if(CurrentlyPlaying==NULL){
			while(temp->next!=head){
				temp=temp->next;
			}
			CurrentlyPlaying=(struct Current*)malloc(sizeof(struct Current)); 
			strcpy(CurrentlyPlaying->Songname,temp->Songname);
			return CurrentlyPlaying;
		}
		else if(strcmp(CurrentlyPlaying->Songname,head->Songname)==0){
			while(temp->next!=head){
				temp=temp->next;
			}
			strcpy(CurrentlyPlaying->Songname,temp->Songname);
			return CurrentlyPlaying;
		}
		
		while(temp->next!=head&&strcmp(temp->next->Songname,CurrentlyPlaying->Songname)!=0){
		
		temp=temp->next;
		}
		
		strcpy(CurrentlyPlaying->Songname,temp->Songname);
		return CurrentlyPlaying;
		}
	else if(strcmp(Placement,"N")==0){
			if(CurrentlyPlaying==NULL){
				CurrentlyPlaying=(struct Current*)malloc(sizeof(struct Current)); 
				strcpy(CurrentlyPlaying->Songname,head->Songname);
				return CurrentlyPlaying;
		}
		while(temp!=NULL&&strcmp(temp->Songname,CurrentlyPlaying->Songname)!=0){
			temp=temp->next;
		}
		if(temp==NULL){
			strcpy(CurrentlyPlaying->Songname,head->Songname);
			return CurrentlyPlaying;
			
		}
		else{
			strcpy(CurrentlyPlaying->Songname,temp->next->Songname);
			return CurrentlyPlaying;
		}
	}
	return CurrentlyPlaying;
}

void MoveSong(struct Node *head ,char songcarry[50],char songref[50],char placement[50] ){
	Node *carry,*ref;
	Node *temp=head;
	Node *temp_temp=head;
	while(temp->next!=head && strcmp(temp->next->Songname,songcarry)!=0){
		temp=temp->next;
	}
	carry=temp->next;
	temp->next=temp->next->next;
	if(strcmp(placement,"B")==0){
		while(strcmp(temp->next->Songname,songref)!=0){
				temp=temp->next;
		}
	
		carry->next=temp->next;
		temp->next=carry;	

		}
	else if(strcmp(placement,"A")==0){
		while(strcmp(temp->Songname,songref)!=0){
				temp=temp->next;
		}
					
			carry->next=temp->next;
			temp->next=carry;
		
		}
		
		
	}
	
	
	

Node* insertAtFront(char songname[50], Node *head) {

    Node *temp=head;
    Node *newNode=(struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->Songname,songname);
    if(head==NULL){
    	newNode->next=newNode;
    	return newNode;
	}
	else{
		while(temp->next!=head){
			temp=temp->next;
		}
	temp->next=newNode;
    newNode->next=head;
    return newNode;
}
  	}
  	
Node* insertAtEnd(char songname[50], Node * head) {
    Node *temp=head;
    Node *newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->next=head;
   	strcpy(newNode->Songname,songname);
    if(temp==NULL){
        head=newNode;
    }
      while(temp->next!=head){
    	temp=temp->next;
	}
   	temp->next=newNode;
	return head;
}


bool stringIsOnlyWhitespace(const char * line) { // function to learn whether aline is empty or not.
    int i;
    for (i=0; line[i] != '\0'; ++i)
        if (!isspace(line[i]))
            return false;
    return true;
}

int main(){
	

	Node* Songlist = NULL;
		Current *CurrentlyPlaying=NULL;
	FILE *fp;
    FILE *fout;
    fp = fopen("input1.txt", "r"); 
    if(fp==NULL){
    	return 0;
	}
    char ch;
    fout=fopen("output.txt","w");
    int line = 0, word = 1, maxchar = 0, icount = 0, maxword = 0;
    int last = '\n';
    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    while ((ch = fgetc(fp)) != EOF) {
    	
        ++icount;
        if (ch == ' ') {
            word++;
            if (word > maxword) {
                maxword = word;
            }

        }
        if ((ch == '\n' || ch == '\r') && last != '\n') {
            word = 1;
            ++line;
            --icount;
            if (icount > maxchar) {
                maxchar = icount;
            }
            icount = 0;
        }
        last = ch;
    }
    char *commandtemp = ((char *) malloc(sizeof(char*) * 1000));
    char *command;
    char **arr;
    arr = (char **) malloc(sizeof(char *) * line);
    int a;
    for (a = 0; a < line; a++) {
        arr[a]=malloc(sizeof(char)*maxchar);
    }
    int i = 0;
    rewind(fp);


    while (fgets(commandtemp, fileSize, fp) != NULL) {
        // not including empty lines from text;
        if (!(stringIsOnlyWhitespace(commandtemp))) {
            command = strtok(commandtemp, "\n,\r");

            arr[i] = strdup(command);

            i++;
        } else {

            continue;
        }
    }


    char *token;
    char *temp = ((char *) malloc(sizeof(char) * maxchar));
    int loop;
	int count =0;
	int k;
	
    for(loop=0;loop<i;loop++){
        strcpy(temp, arr[loop]);
        token = strtok(temp,"\t");
        while (token != NULL) {
     	
            if(strcmp(token,"InsertSong")==0){
            
            	token=strtok(NULL,"\t");
            	if(strcmp(token,"H")==0){
                   	token=strtok(NULL,"\t");
            		Songlist=insertAtFront(token,Songlist);
            		
				}
				else if(strcmp(token,"T")==0){
					token=strtok(NULL,"\t");
					Songlist=insertAtEnd(token,Songlist);
				}
              
			}
			else if(strcmp(token,"MoveSong")==0){
			
					token=strtok(NULL,"\t");
					char *Placement=token;
					token=strtok(NULL,"\t");
					char * songcarry=token;
					token=strtok(NULL,"\t");
					char * songref=token;
					MoveSong(Songlist,songcarry,songref,Placement);
				
				}
			else if(strcmp(token,"RemoveSong")==0){
					
				token=strtok(NULL,"\t");
					if(CurrentlyPlaying!=NULL&&strcmp(token,CurrentlyPlaying->Songname)==0){
						fprintf(fout,"Cannot Remove The Playing Song\n*****\n");
						continue;
					}
				    Delete(token,Songlist);
				 
				}
				
				else if(strcmp(token,"PlaySong")==0){
				
					token=strtok(NULL,"\t");
					CurrentlyPlaying=PlaySong(Songlist,token,CurrentlyPlaying);
					if(CurrentlyPlaying!=NULL){
					fprintf(fout,"Playing\t%s\n*****\n",CurrentlyPlaying->Songname);}
					else{
						fprintf(fout,"No Songs To Play\n*****\n");
					}
					
				}
				else if(strcmp(token,"PrintPlaylist")==0){
					token=strtok(NULL,"\t");
					print(Songlist,token,fout);
				}	
				else if(strcmp(token,"ReversePlaylist")==0){
					if(Songlist==NULL){
						token=strtok(NULL,"\t");  	
						continue;
					}else{
					
					ReversePlaylist(Songlist,Songlist->next,Songlist->next->next,Songlist);
					Songlist=Songlist->next;
				}
				}
				
				  	token=strtok(NULL,"\t");  	
				  	
			}
			    
		}
		
	
	
	return 0;
}

