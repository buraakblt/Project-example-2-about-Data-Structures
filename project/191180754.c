/*
Müzik listesini oluþturmak amacý ile Dairesel Baðlý Liste kullandým. Dairesel Baðlý listenin normal baðlý listeden farký son elemanýnýn bir null'a deðil ilk elemana baðlý olmasýdýr.
Bu Baðlý liste Node yapýlarýndan oluþmuþtur,her bir Node yapýsý gene Node pointeri ile baþka bir Node'u gösterir ve bu þekilde birbirine baðlý bir liste yapýsý oluþur.
Bu yapý ile InsertSong komutu geldikçe bu liste yapýsýnýn baþýna ya da sonuna gelen komuta göre bir Node eklenmiþtir.MoveSong komutunda ise Node pointerinin gösterdiði Node ile oynanarak
Listede Nodelarýn yerlerinde deðiþiklik saðlanmýþtýr.Remove komutunda iste silinmek istenen Node'la olan baðlantý koparýlmýþ daha sonra bu Node free() fonksiyonu ile silinmiþtir.
ReversePlaylist komutunda recursive bir yapý ile Nodelarýn baðlarýnda deðiþiklik yapýlarak terse döndürme iþlemi saðlanmýþtýr,benzer bir yapý PrinntPlaylist komutunun R parametreli halinde de kullanýlmýþtýr.
Þarký isimlerini tutmak içinse bir char array'i kullanýlmýþ.Bu array'in boyutu pdfte belirtildiði gibi en fazla 50 karakter için þeklinde ayarlanmýþtýr.
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

