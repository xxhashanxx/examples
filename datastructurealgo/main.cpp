
#include <functional>
#include <iostream>
#include <queue>
using namespace std;
//pair sum
std::vector<int> twoSum( std::vector<int> nums, int sum){
    vector<int> ans;
    unordered_map<int,int> mp;
    int pos = 0;
    for(auto it = nums.begin(); it != nums.end(); it++){
        int target = sum - *it ;
        auto it2 = mp.find(target);
        if(it2 != mp.end()){
            ans.push_back(it2->second);
            ans.push_back(pos);
        }
        mp.insert({*it,pos});
        pos++;
    }
    return std::vector<int>();
}
////////////////moving window////////////////////////////////
void Space20(char* str){
    int space = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == ' '){
            space++;
        }
    }
    int idx =  strlen(str) + 2*space;
    str[idx] = '\0';
    for(int i = strlen(str) - 1; i >= 0; i--){
        if(str[i] == ' '){
            str[idx - 1] = '0';
            str[idx - 2] = '2';
            str[idx - 3] = '%';
            idx = idx - 3;
        }
        else{
            str[idx - 1] = str[i];
            idx--;
        }
    }
}

string smallestWindow(string str)
{
    int n = str.length();
    if(n = 0)
        return "";

    int dist_count = 0;
    bool visited[256] = {false};
    for(int i = 0; i < n; i++){
        if(visited[str[i]] == false){
            dist_count++;
            visited[str[i]] = true;
        }
    }

    int curr_count[256] = {0};
    int count = 0;
    int start = 0;
    int min_len = INT_MAX;
    int start_index =0;
    for(int i = 0; i < n; i++){
        curr_count[str[i]]++;

        if(curr_count[str[i]] == 1)
            count++;
        if(count == dist_count){
            while(curr_count[str[start]] > 1){
                if(curr_count[str[start]] > 1){
                    curr_count[str[start]]--;
                }
                start++;
            }
        }
        int len_window = i -start +1;
        if(min_len > len_window){
            min_len = len_window;
            start_index = start;
        }

    }
    return str.substr(start_index, min_len);
}

//////////////////merge sort and quick sort////////////////////
void mergeArrays(int x[],int y[],int a[],int s,int e){
    int mid = (s+e)/2;
    int i=s;
    int j = mid+1;
    int k = s;
    while(i<=mid && j<=e){
        if(x[i] < y[j]){
            a[k] = x[i];
            i++;
            k++;
        }else{
            a[k] = y[j];
            j++;
            k++;
        }
    }
    while(i<=mid){
        a[k] = x[i];
        k++;
        i++;
    }
    while(j<=e){
        a[k] = y[j];
        k++;
        j++;
    }
}

void mergeSort(int a[],int s,int e){
    if(s>=e){
        return;
    }
    int mid = (s+e)/2;
    int x[100],y[100];
    for(int i=s;i<=mid;i++){
        x[i] = a[i];
    }
    for(int i=mid+1;i<=e;i++){
        y[i] = a[i];
    }
    mergeSort(x,s,mid);
    mergeSort(y,mid+1,e);
    mergeArrays(x,y,a,s,e);
}

///////////////////// binary sarch //////////////////////////////////////
int lowerbound(int arr[],int n,int key)
{
    int s = 0;
    int e = n - 1;
    int lower = -1;
    while(s<=e){
        int mid = (s+e)/2;
        if(arr[mid] == key){
            lower = mid;
            if(arr[mid -1] == key) {
                e = mid - 1;
            }
            else
                return lower;
        }
        else if(arr[mid] > key){
            e = mid - 1;
        }
        else{
            s = mid + 1;
        }
    }

    return lower;
}


int binary_search_rec(int arr[] , int s,int e , int key)
{
    //int s = 0;
    //int e = n-1;
    if(s<=e)
        return -1;
    int mid = (s+e)/2;
    if(arr[mid] == key)
        return mid;
    else if(arr[mid] > key)
        e = mid -1;
    else
        s = mid +1;
    int resut = binary_search_rec(arr , s,e , key);

    return resut;
}
/////////// link list ///////////////////////////////////////////
class node{
    public:
        int data;
        node* next;
        node(int d){
            data = d;
            next = NULL;
        }
};
void reverse(node* curr){
    node* prev = NULL;
    while(curr->next != NULL){
        node *temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
}
////////////////////Stack and Queue////////////////////
class Stack{
    queue<int> q1,q2;
    void push(int x){
        if(!q1.empty()){
            q1.push(x);
        }else{
            q2.push(x);
        }
    }
    void pop(){
        if(q1.empty()){
            while(!q2.empty()){
                int front = q2.front();
                q2.pop();
                
                if(q2.empty())
                    break;
                q1.push(front);
            }
        }else{
            while(!q1.empty()){
				int front = q1.front();
				q1.pop();
				if(q1.empty()){
					break;
				}
				q2.push(front);
			}
        }
    }
    int top()
    {
        if (q1.empty())
        {
            // shift the elements from q2 to q1
            while (!q2.empty())
            {
                int front = q2.front();
                q2.pop();
                q1.push(front);
                if (q2.empty())
                {
                    return front;
                }
            }
        }
        else
        {
            while (!q1.empty())
            {
                int front = q1.front();
                q2.push(front);
                q1.pop();
                if (q1.empty())
                {
                    // top element of the stack
                    return front;
                }
            }
        }
    }
    bool empty(){
		return q1.empty() && q2.empty();
	}
};

/////// Piority Queue ////////////////////////////
vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
{
    priority_queue<pair<int, pair<int, int>>> pq;
    vector<vector<int>> ans;
    for (int i = 0; i < points.size(); i++)
    {
        int dist = pow(points[i][0], 2) + pow(points[i][1], 2);
        pq.push({dist, {points[i][0], points[i][1]}});
        if (pq.size() > k)
        {
            pq.pop();
        }
    }
    while (!pq.empty())
    {
        auto it = pq.top().second;
        pq.pop();
        vector<int> temp;
        temp.push_back(it.first);
        temp.push_back(it.second);
        ans.push_back(temp);
    }
    return ans;
}

/// Tree///////////////////////////////////////////////////////////////////
class Node{
    public:
        int data;
        Node *left;
        Node *right;
        Node(int n){
            data = n;
            left=right=NULL;
        }
};
void printPreOrder(Node *root){
    if(root == NULL)
        return;
    cout << root->data << ", ";
    printPreOrder(root->left);
    printPreOrder(root->right);

}
void printInOrder(Node *root){
    if(root == NULL)
        return;
    printPreOrder(root->left);
    cout << root->data << ", ";
    
    printPreOrder(root->right);

}
void printPostOrder(Node *root){
    if(root == NULL)
        return;
        
    printPreOrder(root->left);
    printPreOrder(root->right);
    cout << root->data << ", ";

}
void levelOrder(Node * root)
{
    queue<Node *> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node * temp = q.front();
        if(temp == NULL){
            cout << endl;
            q.pop();
            if(!q.empty()){
                q.push(NULL);
            }
        }else{
            q.pop();
            if(temp->left != NULL){
                q.push(temp->left);
            }
            if(temp->right != NULL){
                q.push(temp->right);
            }
            cout << temp->data << ", ";
        }
    }
}
int main()
{
    
    return 1;
}
