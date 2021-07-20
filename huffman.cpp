
       /*


        CREATERD BY - ANKUR KUMAR
        Institue- NIT JAMSHEDPUR
	
	This project is to design compression and decompression programs based on Huffman Coding.
	The idea of Huffman Coding is to minimize the weighted expected length of the code by 
	assigning shorter codes to frequently-used characters and longer codes to less-used charecters.


       */




#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;


// Tree Node

class Node{

    // Public member variables

   public:

     char ch;
     int freq;
     Node *left, *right;



   // Node constructor

   Node(char ch,int freq,Node* left, Node* right)
   {
       this->ch=ch;
       this->freq=freq;
       this->left=left;
       this->right=right;
   }
    

};


// Creating a tree Node

Node* Create_Node(char ch,int freq,Node* left, Node* right)
{
    Node* root= new Node(ch,freq,left,right);

    return root;
}


// Compare class used to order heap

class compare{

   public:

   // () operator overloaded

     bool operator()(Node* left,Node* right)
     {
         return left->freq>right->freq;
     }

};


// Traverse Huffman tree and strore codes of respective charecters in a map

void encode(Node* root, unordered_map<char, string> &huffmanCode,string codes)
{
    if(root==NULL) return;

    // Found a leaf node
    // store the charecter and its corresponding code and return

    if(root->left==NULL && root->right==NULL)
    {
        huffmanCode[root->ch]=codes;
    }

    
    encode(root->left,  huffmanCode , codes+"0");
    encode(root->right,  huffmanCode , codes+"1");


}


// Function to decode the encoded string using Huffman tree we built

void decode(Node* root, string str, string & decoded_str)
{

   // Start at index 0 and move on 
   // As we encounter the leaf node , push back data
   // in the decoded string and reset head pointer to 
   // root of the huffman tree

    int index=0;

    Node* head=root;


    while(index<str.length())
    {  

         if(str[index]=='0')
         {
             head=head->left;
         }

         else{
             head=head->right;
         }

         // encountered a lead node
         // push data into string 
         // and reset head to root

         if(head->left==NULL && head->right==NULL)
         {
             decoded_str.push_back(head->ch);
             head=root;
         }

         index++;
    }



}




// Build Huffman Tree

Node* buildHuffmanTree(string text)
{

    // count frequency of of each character
	// and store it in a hash map

	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

    // Create a priority queue to store nodes of
	// Huffman tree;

	priority_queue<Node*, vector<Node*>, compare> pq;


	// Create a leaf node for each character and add it
	// to the priority queue.

	for (auto pair: freq) {
		pq.push(Create_Node(pair.first, pair.second, NULL, NULL));
	}


    while(pq.size()>1)
    {

        // Remove the two nodes of lowest frequency from the queue
		
		Node *leftChild = pq.top(); pq.pop();
		Node *rightChild = pq.top();	pq.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.

		int sum = leftChild->freq + rightChild->freq;
		pq.push(Create_Node('\0', sum, leftChild, rightChild));


    }


    // root node stores pointer to root of Huffman Tree

	Node* root = pq.top();

    return root;

}





int main()
{

    // For text file input from the system

     #ifndef ONLINE_JUDGE
     freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
      #endif


    string text; 

    getline(cin, text);


    cout<<" Original string was :\n ";
    cout<<endl<<text<<endl;
    cout<<endl;

    
    Node* root=buildHuffmanTree(text);


    // traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
    // Function to encode the sample input

	unordered_map<char, string> huffmanCode;
	encode(root,  huffmanCode, "");




   // prints all the huffman codes with respect to the charecter

	cout << "Huffman Codes are :\n" << endl;

	for (auto pair: huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

    // print encoded string
	string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n \n" << str << '\n';
    
    // Function to decode the encoded string 
    // Takes empty string and returns the decoded sring

     string decoded_str="";    

     decode(root, str,decoded_str);

     cout<<endl<<"decoded string is :"<<endl<<endl;

     cout<<decoded_str<<endl;
    
}




/*

    Sample Input String

    Gon Sometimes you shine so brightly , I must look away. But is it still okay if i stay by your side.  ~ Killua Zoldyck


*/



/*

    Sample Output

     
     Original string was :
 
Gon Sometimes you shine so brightly , I must look away. But is it still okay if i stay by your side.  ~ Killua Zoldyck

Huffman Codes are :

i 1111
o 1110
u 11011
d 110101
b 110100
h 110011
e 11000
s 1011
Z 1010111
f 1010110
~ 1010011
, 1010010
k 00011
n 101010
I 1001111
a 0000
r 100100
  01
. 110010
S 1010000
t 0011
c 1001010
m 00010
K 1001011
y 1000
w 1001100
B 1010001
g 1001101
l 0010
G 1001110

Encoded string is :
 
10011101110101010011010000111000010110000011111100010110001011011000111011011011011110011111110101011000011011111001110100100100111110011011100110011001010000110100100110011110100010110111011001101001011101110000110100001001100000010001100100110100011101100110111111011011111001101101100111111001000100111100001100001000011111101011001111101101100110000100001110100100001100011101101110010001101111111101011100011001001011010011011001011111100100010110110000011010111111000101101011000100101000011

decoded string is :

Gon Sometimes you shine so brightly , I must look away. But is it still okay if i stay by your side.  ~ Killua Zoldyck


*/
