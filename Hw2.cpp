
/*Tomer Ramon - 204621510
  Daniel Nachshoni - 303111744
   Q name: 23. Merge k Sorted Lists
   Difficulty: Hard
   Q description:	 You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
                   Merge all the linked-lists into one sorted linked-list and return it.
   Q link: https://leetcode.com/problems/remove-nth-node-from-end-of-list/

   At the end there is main with 2 test cases and commands all over the code for better understanding.
*/


#include <iostream>
#include <vector>
#include <queue>

// * Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


#define MAX 10000
#define MIN -10000

using namespace std;
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        //we use  priority_queue to save the heads of every list.
        //the queue save 3 element every time and sore them in sorted order
        //every loop we extract the head(smallest)element in the queue and replace him with the next elemet from his own list.
        //at the end we go over 3 lists one time (O(SUM_LISTS_LENGTH))) and every time we remove and insert an elemnt from the queue (O(1)).
        // N = List1+List3+List3

        //total time complexity  = O(N).

        if(lists.size()>10000 || lists.size()<0 ){
            cerr<<"Invalid lists length :"<<lists.size()<<endl;
            exit(1);
        }
        for(auto head : lists){
//            check for invalid input.
            int cnt=0;
            while (head != nullptr){
                cnt++;
                if(head->val<MIN || head->val>MAX){
                    //check all numbers in every list
                    // number in a list is too big or too small.
                    cerr<<"Invalid list number: "<<head->val<<endl;
                    exit(1);
                }
                head=head->next;

            }
            if(cnt<0||cnt>500){
                //checks that there are no more than 500 nodes in every list/
                cerr<<"Invalid list length."<<endl;
                exit(1);
            }

        }
        priority_queue<pair<int,ListNode*>,vector<pair<int,ListNode*>>,greater<pair<int, ListNode*>>>queue;
        //priority_queue - Queue that save all the element in order in this case from small to big( greater function)
        //the queue define be how the element will look = pairs of value(int) and the listNode they relate to(ListNode*).
        //second param is where to save the elements-> in this case we decided to go with vector of pairs.
        //Third param is the method of how sort the elements -> We chose the 'greater' function that sort from small to big.

        for (auto head : lists){
            if (head!=nullptr) {
                queue.push(make_pair(head->val,head)); //build priority_queue of K element = O(K)~O(1).
            }
        }

        ListNode* top=nullptr; //the new marged list
        ListNode* tmp=nullptr; //helper to save location in the new list withpout losing the top pointer.

        while (!queue.empty()){
            //go over the queue and evry time we remove the smallest elmemnt and insert the next elemnet from his list if its not NULL.
            auto head = queue.top();
            queue.pop();
            auto node = head.second;

            if (tmp ==nullptr){ //if the new list we built is empty we intalize it with the smallet element in the queue (the first element)
                tmp=node;
                top=node;
            }
            else {
                tmp->next = node;
                tmp = tmp->next;

            }
            if(node->next!=nullptr){ //insert next element from the spacifixc list if he is not NULL
                queue.push(make_pair(node->next->val,node->next));
            }
        }
        return top;
    }
};


ListNode *mergeKLists(vector<ListNode *> vector1);

void printList(ListNode *pNode);


//testing code with 2 scenarios, first case is a workign merge
//and the second case is when there is an invalid number in one
//of the lists and the program find him , send message and exit the program.

int main(){
    Solution s;

    /*scenario 1 for working merge*/

    ListNode* l1 = new ListNode(1, new ListNode(4,new ListNode(5,nullptr)));
    ListNode* l2 = new ListNode(1,new ListNode(3,new ListNode(4,nullptr)));
    ListNode* l3 = new ListNode(12,new ListNode(13,new ListNode(49,nullptr)));
    ListNode* l4 = new ListNode(21,new ListNode(36,new ListNode(84,nullptr)));
    ListNode* l5 =new  ListNode(2,new ListNode(6,nullptr));

    vector<ListNode*> lists;
    lists.push_back(l1);
    lists.push_back(l2);
    lists.push_back(l3);
    lists.push_back(l4);
    lists.push_back(l5);
    ListNode* ll = s.mergeKLists(lists);
    printList(ll);

    /*end of scenario*/

    /*scenario 2 for not working merge(invalid nu,ber in list (10001))*/

//    auto* l1 = new ListNode(56, new ListNode(400,new ListNode(500,nullptr)));
//    auto* l2 = new ListNode(1,new ListNode(30,new ListNode(9999,nullptr)));
//    auto* l3 =new  ListNode(6,new ListNode(10001,nullptr));
//
//    vector<ListNode*> lists;
//    lists.push_back(l1);
//    lists.push_back(l2);
//    lists.push_back(l3);
//    ListNode* ll = s.mergeKLists(lists);
//    printList(ll);

    /*end of scenario 2*/
    return 0;
}

void printList(ListNode* list){
    cout<<"merged list: ";
    while (list!= nullptr){
        cout<<list->val<<"->";
        list=list->next;
    }
    cout<<"NULL"<<endl;
}