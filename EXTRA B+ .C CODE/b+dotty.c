#include"stdio.h"
#include"stdlib.h"


//Assign an order size, based on your B+ tree requirements.

#define order 5


//structure defination:

struct node

{
    struct node *ptr[order];
    struct node *parent;
    struct node *sibling_ptr;
    int key[order-1];
    
    //type - 1 : internal node. type - 0 : leaf node.
    int type;
    
    //holds no of elements present
    int count;

    int id;
};



//typedef struct node * to NODE

typedef struct node* NODE;

static int gName=0;
int val;int new=0;
//Getnode function:  Allocates Memory Dynamically and assigns 
//                   appropriate default values.


NODE getnode()
{
    int i;
    NODE temp;

    temp=(NODE)malloc(sizeof(struct node));


    for (i=0;i<=order;i++)
    {
        temp->ptr[i]=NULL;
    }

    for (i=0;i<=order-1;i++)
    {
     temp->key[i]=0;
    }

    temp->type=1;
    temp->count=0;
    temp->parent=NULL;
    temp->sibling_ptr=NULL;
    return temp;

}


//Getleaf function:  Allocates Memory Dynamically and assigns 
//                   appropriate default values.



NODE getleaf()
{
    int i;
    NODE temp;

    temp=(NODE)malloc(sizeof(struct node));


    for (i=0;i<=order;i++)
    {
        temp->ptr[i]=NULL;
    }

    for (i=0;i<=order-1;i++)
    {
     temp->key[i]=0;
    }

    temp->type=0;
    temp->count=0;
    temp->parent=NULL;
    temp->sibling_ptr=NULL;
    return temp;

}

  


//Global data:

int height,k,t=0,i=0;



//Function declaration.

NODE insert_parent(NODE ,NODE ,NODE ,int );



//find_leaf :  Searches for the required leaf node and return 
//             the same.


NODE find_leaf(NODE temp, int key)
{

    int position=0,i;


    //If the key already exists in the tree,EXIT.

    for (i=0;i<temp->count;i++)
    {

        if (key==temp->key[i])
        {
            printf("No duplicates allowed\n");
            exit(0);
        }

    }


    //As soon as the leaf node is encountered i.e leaf->type 
    //is 0,Return that leaf.

    if (temp->type==0)
    {
      return temp;
    }



    //To calculate position,Based on which link to follow.

    for (i=0;i<temp->count;i++)
    {
        
        if (temp->key[i] < key)
        {
            position++;
        }

    }

   
    //To traverse to that node

    temp=temp->ptr[position];


    //Call recursively

    find_leaf(temp,key);
 

}


//display_leaf : Displays all the leafnodes in order.


void display_leaf(NODE temp)
{
 
  int i;

 //Traverse till the leaf node level from root.

   while(temp->ptr[0]!=NULL)
  { 
    temp=temp->ptr[0]; 
  }

  
  //Print all the keys of the given leaf node. 

  while(temp!=NULL)
  {

     for(i=0;i<order-1;i++)
     {
      printf("%d |",temp->key[i]);
     }


     printf("\t");


     //Traverse to the next leaf node with the help of 
     //sibling pointer.

     temp=temp->sibling_ptr;

  }


}


//dislplay:  Displays all the nodes in Preorder Fashion.


void display(NODE temp)

{ 

   int i; 
 
   //Case 1:If root is NULL.  
  
   if(temp==NULL)
   {
    return;
   }
  

   printf("\n");
  

   //Print all the keys of the node.

   for(i=0;i<order-1;i++)
   {
    printf("%d |",temp->key[i]);
   }
  
  
   //Traverse to the next node.

   for(i=0;i<order;i++)
   {
    display(temp->ptr[i]); 
   }
   

}



//split_parent:  As parent is full, split parent node and send its intermediate value
//               back to insert_parent.


NODE split_parent(NODE root,NODE Parent,NODE leaf2,int position,int var)
{

    NODE new_node;
    NODE temp_pointer[order+1];
    int temp_key[order];
    int klength,plength,i,j=0,k;
    int pvar;//the element to be passed recursively up the tree.


    new_node=getnode();
    new_node->id=new++;

    //FOR Pointers.


    //Copy pointers of parent into temp

    for (i=0;i<order;i++)
    {
        temp_pointer[i]=Parent->ptr[i];
    }


    //Shift pointers one step ahead from the position pointer to make 
    //room for the new pointer(leaf2).

    for (i=order-1;i>position;i--)
    {
        temp_pointer[i+1]=temp_pointer[i];
    }

    
    // Assign the pointer at location 'position+1' to leaf2

    temp_pointer[position+1]=leaf2;


    //FOR Keys.


    //Copy all keys to the temp_key.

    for (i=0;i<order-1;i++)
    {
        temp_key[i]=Parent->key[i];
    }

    
    //Make space for the key by shifting by one position ahead appropriately.

    for (i=order-1;i>position;i--)
    {
        temp_key[i]=temp_key[i-1];
    }


    //Insert the intermidiate value 'var'.

    temp_key[position]= var;



    //Erase parent.

    Parent->count=0;
   
        for (i=0;i<order;i++)
    {
        Parent->ptr[i]=NULL;
    }


    for (i=0;i<=order-1;i++)
    {
     Parent->key[i]=0;
    }




    //To Determine split length

    //The below block performs the same functionality as ceiling function.

    
    klength = order-1;

    if (klength%2==0)
    {
        klength=klength/2;
    }
    
    else
    {
        klength=(klength/2)+1;
    }

    
    
    plength = order;

    if (plength%2==0)
    {
        plength=plength/2;
    }
    
    else
    {
        plength=(plength/2)+1;
    }



    //Copy the first half of the Pointer,Key from temp into Parent.

    for (k=0;k<plength;k++)
    {
        Parent->ptr[k]=temp_pointer[k];
    }


    for (i=0;i<klength;i++)
    {

        Parent->key[i]=temp_key[i];
        Parent->count++;

    }



    //pvar is the intermidiate value to be passed up the tree, 
    //Unlike var it is not present in leafnode.

    pvar=temp_key[klength];


    //Copy the next pointer,key pairs from temp to new_node.

    for (k=plength,j=0;k<order+1;k++,j++)
    {
        new_node->ptr[j]=temp_pointer[k];
    }



    for (i=klength+1,j=0;i<order;i++,j++)
    {
        new_node->key[j]=temp_key[i];
        new_node->count++;
    }


    //Assign parent to new_node.

    new_node->parent = Parent->parent;



    //The new_node(new parent) obtains all the child links from temp.
    //But the child links look up to Parent(old parent) as its parent.
    //Therefore link the parent of all these child nodes to the new_node(new parent).

    for (i=0;i<=new_node->count;i++)
    {
        (new_node->ptr[i])->parent = new_node;
    }

   
    Parent->type=1;
    new_node->type=1;     


    //Call recursively(from insert_parent) till it encounters a Node which has less than order no of elements.
    //The above function splits even the root.Then in insert_parent the new parent is made root.

    return insert_parent(root,Parent,new_node,pvar);


}




//insert_parent:  Inserts element into parent node.

NODE insert_parent(NODE root,NODE leaf1,NODE leaf2,int var)
{

    NODE Parent=getnode();
    int position=0,i;
 

    //Assign parent node.

    Parent=leaf1->parent;


    //New root,if parent is null.

    if (Parent==NULL)
    {
     
        Parent=getnode();
     
        Parent->key[0]=var;
        Parent->count++;
     
        Parent->ptr[0]=leaf1;
        Parent->ptr[1]=leaf2;
     
        leaf1->parent=Parent;
        leaf2->parent=Parent;
        Parent->id=new++;
        return Parent;

    }


    //Root is not null.

    //To determine the position of the link to leaf1 in the parent.
 

    while (position < Parent->count && (Parent->ptr[position])->key[0]!=leaf1->key[0])
    {
   
        position++;

    }

    
    //So now we have the position of the pointer which points to leaf1.

    //Case 1:Parent has space to accomodate intermediate value 'var'.

    
    if (Parent->count < order -1)
    {
       
        //make room for 'var' by shifting elements one place ahead(till position).

   
        for (i=Parent->count;i>position;i--)
        {
            Parent->key[i]=Parent->key[i-1];
        }

   
        for(i=Parent->count;i>=position;i--)
        {
           Parent->ptr[i+1]=Parent->ptr[i];     
        }



        //Place the intermediate value in its appropriate place.

        Parent->key[position]=var;
        Parent->count++;
        
        Parent->ptr[position+1]=leaf2;
  
        return root;
   
     }



  //Case 2:Parent is full,therefore split parent.

  return split_parent(root,Parent,leaf2,position,var);

  
}




//insert_leaf:  Insert into the leaf when space is available in it .


NODE insert_leaf(NODE leaf,int key)
{

    int i,position=0;

 
    //Determining the position as to where the key should be placed.

    
    while (leaf->key[position] < key && position<leaf->count)
    {
        position++;
    }
 
    
    // shifting elements one position ahead(till position), to make space for the new key.

    
    for (i=leaf->count;i>position;i--)
    {
        leaf->key[i]=leaf->key[i-1];
    }

    
    leaf->key[position]=key;
    leaf->count++;

    return leaf;


}



//splitLeaf:  Split node as leaf is full.

NODE splitLeaf(NODE root,NODE leaf,int key)

{

    NODE new_leaf;
    
    int temp[order];
    int position=0,var,length,k,j;
    struct node* paRent;
    struct node* sibling;
    

    new_leaf=getleaf();
    new_leaf->id=new++;

    //Copy the contents of leaf to temp.

    for (i=0;i<leaf->count;i++)
    {
        temp[i]=leaf->key[i];
    }




    //Determine the position, as where the key should be placed.

    while (leaf->key[position] < key && position < leaf->count)
    {
        position++;
    }
  

    //shift ahead all the elements from position by one, to make room for the key.

     k=order-1;

    
     while(position<k)
     {
        temp[k]=temp[k-1];
        k--;
     }    


    //insert key.

    temp[position]=key;



    // erase leaf.
    
    leaf->count=0;
   

    for (i=0;i<=order-1;i++)
    {
      leaf->key[i]=0;
    }



    //Determine split length

    //The below block performs the task of the ceiling function.


    length=order-1;

    if (length%2==0)
    {
        length=length/2;
    }

    else
    {
        length=(length/2)+1;
    }


    //Put values into leaf uptil length.

    
    for (i=0;i<length;i++)
    {
        leaf->key[i]=temp[i];
        leaf->count++;
    }



    //Put values into new_leaf from the position of length till the order, 
    //as the leaf was full before insertion.

    
    for (j=0;i<order;i++,j++)
    {
        new_leaf->key[j]=temp[i];
        new_leaf->count++;
    }

    
    

    //Assign parent to new_leaf.

    new_leaf->parent = leaf->parent;

    
    //Assign appropriate sibling pointer.

    new_leaf->sibling_ptr = leaf->sibling_ptr;
    leaf->sibling_ptr = new_leaf;


    //To determine the intermediate value to be passed up the tree.

    var=new_leaf->key[0];


    return insert_parent(root,leaf,new_leaf,var);


}

FILE *outputFile;
void preorderDotDump (NODE root, FILE* outputFile)
{
   
       int i;   
    if (root != NULL)
    {
       
           
        fprintf (outputFile, "node%d[label=\"<f0>%d",root->id,root->key[0]);
           
            i=1;
            while(root->key[i]!='\0')
            {           
           
                fprintf (outputFile, "|<f%d>%d",
                    i,root->key[i]);
                i++;           
            }
            fprintf (outputFile,"\"];\n");   
            i=0;
               
                while(root->ptr[i]!=NULL)
                {           
                                   
                    fprintf (outputFile, "\"node%d\":f%d -> \"node%d\":f%d;\n", root->id,0, root->ptr[i]->id,0);
                    i++;           
                }
                   
            i=0;
                while(root->ptr[i]!=NULL) //recursive call
            {           
                preorderDotDump (root->ptr[i], outputFile);
               
                i++;           
            }
           
           
        }
}

   








void dotDump(NODE root, FILE *outFile)
{
    gName++;
    fprintf (outFile, "digraph tree{\n node [shape = record];\n",gName);
   // if(flg==1)
        preorderDotDump (root, outFile);
        fprintf (outFile, "}\n");
}







//insert:  Main insert function.

NODE insert(NODE root,int key)

{

  
    NODE leaf;
   
   
    //Case 1: when root is NULL.
 
    if(root->key[0]==0)

    {

     root->key[0]=key;
     root->count++;
     root->id=new++;
     return root;

    }



    //Find the Appropriate leaf node where the key should be inserted.
   
    leaf=find_leaf(root,key);
   

    // Leaf has space for key
  
    if (leaf->count < order-1 )
    {
       
        insert_leaf(leaf,key);
        return root;
    }


    //No space in the leaf node, therefore split.
 
    return splitLeaf(root,leaf,key);
  

}


//main:  MAIN FUNCTION.


int main(int argc, char** argv)
{
    FILE *pipe;
    NODE root=NULL;
    root=getleaf();
    int ch,key,i;
                if (argc != 2)
		{
			printf(" need one argument  \n");
			exit(0);
		}

		outputFile = fopen ("bst.dot", "w");
    		fclose (outputFile);
		val = atoi(argv[1]);
    
                for(i=0;i<val;i++)
		{
			key=random()%1000;
			printf("%d\t",key);
			root=insert(root,key); 

						
			outputFile = fopen ("bst.dot", "a");
			if (outputFile != NULL) 
			{
					        	
				dotDump (root,  outputFile);
			}
			fclose (outputFile);
		}						
					







/*      printf("Enter your choice:\n");
      printf("1.Insert 2.Exit\n");
      scanf("%d",&ch);

      if (ch==1)
      {*/
    /*
        printf("Enter key:");
        scanf("%d",&key);
    */
      //  root=insert(root,key);
                               outputFile = fopen ("bst.dot", "a");
					dotDump (root,  outputFile);
					fclose (outputFile);

                                 pipe=popen("dot -Tps bst.dot -o bst.ps","w");
					pclose(pipe);	
					pipe=popen("evince bst.ps","r"); 
					pclose(pipe);  
//        printf("\n");
        display(root);
    
//        printf("\n\n");
//        display_leaf(root);
   
     
   /*
     else
     {
        exit(0);
     }
*/

    


}



