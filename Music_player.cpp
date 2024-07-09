#include<bits/stdc++.h>

using namespace std;

struct SongNode{
    string song;
    SongNode* prev=NULL;
    SongNode* next=NULL;
};

stack<string> stk;
queue<string> q;

void add_song(SongNode*& last){
    if(last==NULL){
        SongNode* new_song=new SongNode();
        cout<<"Please enter the song name:\n";
        cin>>new_song->song;
        last=new_song;
    }
    else{
        SongNode* new_song=new SongNode();
        cout<<"Please enter the song name:\n";
        cin>>new_song->song;
        last->next=new_song;
        new_song->prev=last;
        last=new_song;
    }
    cout<<"Song added to playlist successfully.\n";
}

void count_songs(SongNode* start, int& c){
    int cnt=0;
    while(start){
        start=start->next;
        cnt++;
    }
    cout<<"The number of songs are: "<<cnt<<endl;
    c=cnt;
}

void del_song(SongNode*& start, SongNode*& last){
    cout<<"Please choose one of the two options:\n1. Delete by song number \n2. Delete by song name\n";
    int choice;
    cin>>choice;
    if(choice==1){
        int n, cnt;
        count_songs(start,cnt);
        cout<<"Enter song number\n";
        cin>>n;
        if(n>cnt){
            cout<<"Song number is out of range.\n";
            cout<<"1. Reenter song number\n2. Exit";
            int x;
            cin>>x;
            if(x==1) del_song(start,last);
            else return;
        }
        int i=1;
        SongNode* prev=NULL, *cur=start;
        for(int i=1; i<n; i++){
            cur=cur->next;
        }
        if(n==1){ 
            start=start->next != NULL ? start->next : NULL;
            if(start) start->prev=NULL;
        }
        else if(n==cnt) {
            last=last->prev!=NULL ? last->prev : NULL;
            if(last) last->next=NULL;
        }
        else{
            cur->prev->next=cur->next;
            cur->next->prev=cur->prev;
        }
        delete cur;    
    }
    else{
        string s;
        cout<<"Please enter the name of song to be deleted:\n";
        cin>>s;
        if(start->song==s){
            start=start->next != NULL ? start->next : NULL;
            delete start->prev;
            if(start) start->prev=NULL;
        }
        if(last->song==s){
            last=last->prev!=NULL ? last->prev : NULL;
            delete last->next;
            if(last) last->next=NULL;
        }
        else{
            SongNode* cur=start;
            while(cur && cur->song!=s){
                cur=cur->next;
            }
            if(cur==NULL){
                cout<<"Song not found in the playlist.\n";
                cout<<"1. Reenter song number\n2. Exit";
                int x;
                cin>>x;
                if(x==1) del_song(start,last);
                else return;
            }
            else{
                cur->next->prev=cur->prev;
                cur->prev->next=cur->next;
                delete cur;
            }
        }
    }
}

void printlist(SongNode* start){
    if(start==NULL){
        cout<<"There are np songs in the playlist currently! :(\n";
    }
    else{
        cout<<"Following songs are coming up next: ";
        while(start){
            cout<<start->song<<"\n";
            start=start->next;
        }
    }
}

void play(SongNode* start){
    if(!q.empty()){
        string cur=q.front();
        if(!stk.empty() && stk.top()!=cur) stk.push(cur);
        cout<<"Now playing: "<<cur<<"\n";
        cout<<"🎵🎶.....\n";
        return;
    }
    if(start==NULL) cout<<"Please add songs into the playlist first.";
    else{
        cout<<"Now playing: "<<start->song<<"\n";
        cout<<"🎵🎶.....\n";
    }
}

void next_song(SongNode* start){
    if(!q.empty()){
        q.pop();
        return;
    }
    if(start==NULL) cout<<"There is no next song";
    else{
        start=start->next;
    }
}

void  end_node(){
    cout<<"Thank you for using our application! \nPlease visit us again :)\n";
}

void addto_q(){
    string s;
    cout<<"Please enter the song name: ";
    cin>>s;
    q.push(s);
}

void recent_songs(){
    if(stk.empty()){
        cout<<"You have'nt played any song yet.\n";
        return;
    }
    cout<<"You have listened to following songs recently:\n";
    stack<string> r=stk;
    while(!r.empty()){
        cout<<r.top()<<"\n";
        r.pop();
    }
}

void qsongs(){
    if(q.empty()){
        cout<<"You haven't added any song to queue yet.\n";
    }
    else{
        cout<<"Following songs have been added to queue:\n";
        queue<string> qu=q;
        while(!qu.empty()){
            cout<<qu.front()<<"\n";
            qu.pop();
        }
    }
}

int main(){
    SongNode* start=NULL, *tail=NULL;
    while(true){
        cout<<"Choose one option: \n1.Add a song\n2. Delete a song\n3. Count number of songs in queue\n4. Print all the song\n5. Start playing song\n6. Skip to next song\n7. Add a song to queue\n8. View recently played songs\n9. View songs in queue\n10. Exit\n";
        int choice, temp;
        cin>>choice;
        if(choice==1) {
            add_song(tail);
            if(start==NULL) start=tail;
        }
        else if(choice==2) del_song(start, tail);
        else if(choice==3) count_songs(start,temp);
        else if(choice==4) printlist(start);
        else if(choice==5) play(start);
        else if(choice==6) next_song(start);
        else if(choice==7) addto_q();
        else if(choice==8) recent_songs();
        else if(choice==9) qsongs();
        else if(choice==10){
            end_node();
            break;
        }
       
    }
    return 0;
}
