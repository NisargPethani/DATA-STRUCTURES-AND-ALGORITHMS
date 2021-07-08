#include<bits/stdc++.h>
#include<sys/stat.h> 

#define MAX_LEN 2097152
#define SIZE 1024
#define MAX_FILES_TOGETHER 512

#define ll long
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define rrep(i,b,a) for(ll i=b;i>=a;i--)

#define TIME cout<< "\nTime elapsed:   " << 1000 * clock() / CLOCKS_PER_SEC << " m-sec => "<< (float)clock() / CLOCKS_PER_SEC<<" sec => "<< ( (float)clock() / (CLOCKS_PER_SEC * 60) )<<" min\n";

using namespace std;


class heap{

    vector<ll> data;
    vector<ll> pos;
    ll total_ele;
    ll max_ele;
    
    public:

        heap(){
            max_ele = SIZE;
            total_ele = 0;

            data = vector<ll>(max_ele,0);
            pos = vector<ll>(max_ele,0);

            rep(i,0,max_ele){
                pos[i] = i;
            }
        }

        heap(ll input_size){

            max_ele = 1;
            while(max_ele<input_size){
                max_ele<<=1;
            }

            total_ele = 0;
            data = vector<ll>(max_ele,0);
            pos = vector<ll>(max_ele,0);

            rep(i,0,max_ele){
                pos[i] = i;
            }
        }

        ll getParentIndex(ll child_ind){
            return (child_ind-1)/2;
        }

        ll getLeftChildIndex(ll parent_ind){
            return parent_ind*2 + 1;
        }

        ll getRightChildIndex(ll parent_ind){
            return parent_ind*2 + 2;
        }

        void print(){
            cout<<"HEAP["<<total_ele<<"]: ";
            rep(i,0,max_ele){
                cout<<data[i]<<"-"<<pos[i]<<" ";
            }
            cout<<endl;
        }

        void push(ll input){

            if(total_ele == max_ele){
                return;
            }

            data[total_ele++] = input;
            
            ll ind = total_ele-1;

            ll left_child_ind;
            ll right_child_ind;
            ll parent_ind;

            ll min_sibling_ind;

            while(true){

                if(ind == 0){
                    return;
                }else{

                    if(ind&1 == 1){
                        left_child_ind = ind;
                        right_child_ind = ind+1 < total_ele ? ind + 1: -1;
                    }else{
                        left_child_ind = ind-1;
                        right_child_ind = ind;
                    }

                    if(right_child_ind > -1){
                        if(data[left_child_ind] <= data[right_child_ind]){
                            min_sibling_ind = left_child_ind;
                        }else{
                            min_sibling_ind = right_child_ind;
                        }
                    }else{
                        min_sibling_ind = left_child_ind;
                    }

                    parent_ind = getParentIndex(min_sibling_ind);

                    if(data[parent_ind] <= data[min_sibling_ind]){
                        return;
                    }else{
                        swap(data[parent_ind] , data[min_sibling_ind]);
                        swap(pos[parent_ind] , pos[min_sibling_ind]);
                        ind = parent_ind;
                    }
                }                   
            }
        }

        void pop(){
            
            if(total_ele == 0){
                return;
            }

            ll parent_ind = 0;
            
            swap(data[0], data[total_ele-1]);
            swap(pos[0], pos[total_ele-1]);
            total_ele--;

            ll left_child_ind;
            ll right_child_ind;

            ll min_sibling_ind;

            while(true){
                left_child_ind = getLeftChildIndex(parent_ind);
                right_child_ind = getRightChildIndex(parent_ind);

                if(left_child_ind<total_ele && right_child_ind<total_ele){
                    if(data[left_child_ind] <= data[right_child_ind]){
                        min_sibling_ind = left_child_ind;
                    }else{
                        min_sibling_ind = right_child_ind;
                    }

                    if(data[parent_ind] <= data[min_sibling_ind]){
                        return;
                    }else{
                        swap(data[parent_ind] , data[min_sibling_ind]);
                        swap(pos[parent_ind] , pos[min_sibling_ind]);
                        parent_ind = min_sibling_ind;
                    }

                }else{ 
                    if(left_child_ind<total_ele){
                        if(data[parent_ind] > data[left_child_ind]){
                            swap(data[parent_ind] , data[left_child_ind]);
                            swap(pos[parent_ind] , pos[left_child_ind]);
                        }
                    }
               
                    return;
                }
            }
        }

        ll top(){
            return data[0];
        }

        ll topPos(){
            return pos[0];
        }

        bool empty(){
            return !total_ele;
        }

        bool checkHeap(){
            rep(i,0,total_ele/2){
                if( data[i] > data[getLeftChildIndex(i)] || ( (getRightChildIndex(i) < total_ele) && data[i] > data[getRightChildIndex(i)] ) ){
                    return false;
                }
            }
            return true;
        }

        void resetHeap(){
            total_ele = 0;
            rep(i,0,max_ele){
                data[i] = 0;
                pos[i] = i;
            }
        }
       
};

void merge(ll *arr, ll start_ind, ll mid_ind, ll end_ind){

    ll left_ele = mid_ind-start_ind+1;
    ll right_ele = end_ind-mid_ind;

    ll * left_half = (ll *)malloc(sizeof(ll) * left_ele);
    ll * right_half = (ll *)malloc(sizeof(ll) * right_ele);

    rep(i,0,left_ele){
        left_half[i] = arr[start_ind+i];   
    }

    rep(i,0,right_ele){
        right_half[i] = arr[mid_ind+1+i];  
    }

    ll l=0;
    ll r=0;
    ll k=start_ind;

    while( l<left_ele && r<right_ele ){
        if(left_half[l] <= right_half[r] ){
            arr[k++] = left_half[l++];
        }else{
            arr[k++] = right_half[r++];
        }
    }

    while(l<left_ele){
        arr[k++] = left_half[l++];
    }

    while(r<right_ele){
        arr[k++] = right_half[r++];
    }

    free(left_half);
    free(right_half);
}

void mergeDriver(ll *arr, ll start_ind, ll end_ind){

    if(start_ind>=end_ind){
        return;
    }

    ll mid_ind = start_ind + (end_ind - start_ind)/2;

    mergeDriver(arr, start_ind, mid_ind);
    mergeDriver(arr, mid_ind+1, end_ind);

    merge(arr, start_ind, mid_ind, end_ind);
}

void mergeSort(ll *arr, ll n){    
    mergeDriver(arr, 0, n-1);
}

bool readNumFromFile(FILE *fp, ll *num){
    if(fp == NULL){
        return false;
    }

    char ch;
    string num_str;

    while((ch=getc(fp)) != ',' && ch != EOF){
        num_str.push_back(ch);
    }
    
    if(ch == EOF && num_str.length() == 0){
        return false;
    }else{
        *num = stoll(num_str); 
        return true;
    }
}

int main(int argc, char* argv[]){

    char * input_file_name = argv[1];
    char * out_file_name = argv[2];

    // cout<<input_file_name<<endl;
    // cout<<out_file_name<<endl;

    FILE *input_file = fopen(input_file_name,"r");
    // FILE *input_file = fopen("in","r");

    char ch;
    ll total_number = 1;
    ll output_file_counter = 1; 

    string output_dir = "out_file_dir";
    mkdir(output_dir.c_str(),0777);

    string output_folder = output_dir +"/"+"dir_lev_0"; 
    mkdir(output_folder.c_str(),0777);

    ll file_nums_counter = 0;

    string output_file_name;
    string output_file_path;

    FILE *output_file;
    string num_str, out_num_str;

    ll * arr = (ll *) malloc(sizeof(ll) * MAX_LEN);

    while((ch=getc(input_file)) != EOF){
        if(ch == ','){
            arr[file_nums_counter]=stoll(num_str);

            file_nums_counter++;
            num_str.clear();
        }else{
            num_str.push_back(ch);
        }

        if(file_nums_counter == MAX_LEN){
            mergeSort(arr, file_nums_counter);

            output_file_name = "out_file_" + to_string(output_file_counter-1) + ".txt";
            output_file_path = output_folder + "/" + output_file_name;

            output_file = fopen(output_file_path.c_str(), "w");

            rep(i,0,file_nums_counter-1){
                
                out_num_str = to_string(arr[i]) + ",";
                fputs(out_num_str.c_str(), output_file);
            }

            out_num_str = to_string(arr[file_nums_counter-1]);
            fputs(out_num_str.c_str(), output_file);

            fclose(output_file);

            file_nums_counter=0;
            output_file_counter++;
        }        
    }

    arr[file_nums_counter]=stoll(num_str);

    file_nums_counter++;
    num_str.clear();

    if(file_nums_counter <= MAX_LEN){
        cout<<file_nums_counter<<endl;

        mergeSort(arr, file_nums_counter);

        output_file_name = "out_file_" + to_string(output_file_counter-1) + ".txt";
        output_file_path = output_folder + "/" + output_file_name;

        output_file = fopen(output_file_path.c_str(), "w");

        rep(i,0,file_nums_counter-1){
            
            out_num_str = to_string(arr[i]) + ",";
            fputs(out_num_str.c_str(), output_file);
        }

        out_num_str = to_string(arr[file_nums_counter-1]);
        fputs(out_num_str.c_str(), output_file);

        fclose(output_file);
    } 

    fclose(input_file);

    cout<<"Total Files Written: "<<output_file_counter<<endl;
    cout<<"Total Nums Written: "<<((output_file_counter-1)*MAX_LEN)+file_nums_counter<<endl;
    

    ll prev_lev = 0;
    ll next_lev;

    ll prev_lev_file_count = output_file_counter;
    ll next_lev_file_count;

    string next_lev_file_name;
    string next_lev_dir;
    string next_lev_file_path;

    string prev_lev_file_name;
    string prev_lev_dir;
    string prev_lev_file_path;

    FILE * prev_lev_file_ptr[MAX_FILES_TOGETHER];
    FILE * next_lev_file_ptr;

    ll num;
    bool valid_num;

    heap heap(MAX_FILES_TOGETHER);
    ll heap_top, heap_top_pos;

    if(prev_lev_file_count > 1){

        while(prev_lev_file_count > 1){
            prev_lev_dir = output_dir + "/dir_lev_" + to_string(prev_lev);

            next_lev = prev_lev + 1;
            next_lev_file_count = ceil( (float)prev_lev_file_count / MAX_FILES_TOGETHER);

            next_lev_dir = output_dir + "/dir_lev_" + to_string(next_lev);
            mkdir(next_lev_dir.c_str(),0777);

            
            cout<<endl<<endl;
            cout<<"PRE: "<<prev_lev<<"  :  "<<"NEXT: "<<next_lev<<endl;
            cout<<"P: "<<prev_lev_file_count<<endl;
            cout<<"N: "<<next_lev_file_count<<endl;


            if(prev_lev_file_count <= MAX_FILES_TOGETHER){
                
                heap.resetHeap();

                // pre work
                ll i=0;
                ll prev_lev_file_start = i*MAX_FILES_TOGETHER;
                ll prev_lev_file_end = prev_lev_file_count;

                ll prev_lev_merge_file_count = prev_lev_file_count - prev_lev_file_start;
                
                cout<<"\tNEXT_"<<i<<" : {"<<prev_lev_file_start<<"-"<<prev_lev_file_end-1<<"} : ["<<prev_lev_merge_file_count<<"]"<<endl;
                
                // file opening
                rep(j,0,prev_lev_merge_file_count){

                    prev_lev_file_name = "out_file_" + to_string(prev_lev_file_start + j) + ".txt";
                    prev_lev_file_path = prev_lev_dir + "/" + prev_lev_file_name;

                    prev_lev_file_ptr[j] = fopen(prev_lev_file_path.c_str(),"r");
                }

                next_lev_file_ptr = fopen(out_file_name,"w");


                // WORK
                rep(j,0,prev_lev_merge_file_count){
                    valid_num = readNumFromFile(prev_lev_file_ptr[j], &num);
                    heap.push(num);
                    // cout<<num<<" ";
                }

                heap_top = heap.top();
                heap_top_pos = heap.topPos();

                heap.pop();

                valid_num = readNumFromFile(prev_lev_file_ptr[heap_top_pos], &num);  
                if(valid_num){
                    heap.push(num);
                }

                out_num_str = to_string(heap_top);
                fputs(out_num_str.c_str(), next_lev_file_ptr); 

                while(!heap.empty()){
                    heap_top = heap.top();
                    heap_top_pos = heap.topPos();

                    heap.pop();

                    valid_num = readNumFromFile(prev_lev_file_ptr[heap_top_pos], &num);  
                    if(valid_num){
                        heap.push(num);
                    }

                    out_num_str = "," + to_string(heap_top);
                    fputs(out_num_str.c_str(), next_lev_file_ptr); 
                }
                // cout<<endl;


                // file closing
                rep(j,0,prev_lev_merge_file_count){
                    fclose(prev_lev_file_ptr[j]);

                    prev_lev_file_name = "out_file_" + to_string(prev_lev_file_start + j) + ".txt";
                    prev_lev_file_path = prev_lev_dir + "/" + prev_lev_file_name;

                    remove(prev_lev_file_path.c_str());
                }
                fclose(next_lev_file_ptr);
        
            }else{

                rep(i,0,next_lev_file_count){

                    heap.resetHeap();

                    // pre work
                    ll prev_lev_file_start = i*MAX_FILES_TOGETHER;
                    ll prev_lev_file_end = prev_lev_file_start + MAX_FILES_TOGETHER;

                    ll prev_lev_merge_file_count = MAX_FILES_TOGETHER;

                    if(prev_lev_file_end > prev_lev_file_count){
                        prev_lev_file_end = prev_lev_file_count;
                        prev_lev_merge_file_count = prev_lev_file_count - prev_lev_file_start;
                    }

                    
                    cout<<"\tNEXT_"<<i<<" : {"<<prev_lev_file_start<<"-"<<prev_lev_file_end-1<<"} : ["<<prev_lev_merge_file_count<<"]"<<endl;
                    

                    // file opening
                    rep(j,0,prev_lev_merge_file_count){

                        prev_lev_file_name = "out_file_" + to_string(prev_lev_file_start + j) + ".txt";
                        prev_lev_file_path = prev_lev_dir + "/" + prev_lev_file_name;

                        prev_lev_file_ptr[j] = fopen(prev_lev_file_path.c_str(),"r");
                    }

                    next_lev_file_name = "out_file_"+to_string(i)+".txt";
                    next_lev_file_path = next_lev_dir + "/" + next_lev_file_name;
                    next_lev_file_ptr = fopen(next_lev_file_path.c_str(),"w");


                    // WORK
                    rep(j,0,prev_lev_merge_file_count){
                        valid_num = readNumFromFile(prev_lev_file_ptr[j], &num);
                        heap.push(num);
                        // cout<<num<<" ";
                    }

                    heap_top = heap.top();
                    heap_top_pos = heap.topPos();

                    heap.pop();

                    valid_num = readNumFromFile(prev_lev_file_ptr[heap_top_pos], &num);  
                    if(valid_num){
                        heap.push(num);
                    }

                    out_num_str = to_string(heap_top);
                    fputs(out_num_str.c_str(), next_lev_file_ptr); 

                    while(!heap.empty()){
                        heap_top = heap.top();
                        heap_top_pos = heap.topPos();

                        heap.pop();

                        valid_num = readNumFromFile(prev_lev_file_ptr[heap_top_pos], &num);  
                        if(valid_num){
                            heap.push(num);
                        }

                        out_num_str = "," + to_string(heap_top);
                        fputs(out_num_str.c_str(), next_lev_file_ptr); 
                    }
                    // cout<<endl;
                    
                    // file closing
                    rep(j,0,prev_lev_merge_file_count){
                        fclose(prev_lev_file_ptr[j]);

                        prev_lev_file_name = "out_file_" + to_string(prev_lev_file_start + j) + ".txt";
                        prev_lev_file_path = prev_lev_dir + "/" + prev_lev_file_name;

                        remove(prev_lev_file_path.c_str());
                    }
                    fclose(next_lev_file_ptr);

                }
            }        
    
            prev_lev = next_lev;
            prev_lev_file_count = next_lev_file_count;

            prev_lev_dir = output_dir + "/dir_lev_" + to_string(prev_lev-1);
            remove(prev_lev_dir.c_str());

            cout<<endl<<prev_lev_dir<<" DELETED"<<endl;
        }
    }else if(prev_lev_file_count == 1){

        prev_lev_file_name = "out_file_0.txt";
        prev_lev_dir = output_dir + "/dir_lev_0";

        prev_lev_file_path = prev_lev_dir + "/" + prev_lev_file_name;
        next_lev_file_ptr = fopen(prev_lev_file_path.c_str(),"r");
        
        output_file = fopen(out_file_name,"w");

        while((ch=getc(input_file)) != EOF){
            fputc(ch,output_file);
        }

        fclose(output_file);
        fclose(next_lev_file_ptr);

        remove(prev_lev_file_path.c_str());        
    }

    prev_lev_dir = output_dir + "/dir_lev_" + to_string(prev_lev);
    remove(prev_lev_dir.c_str());
    cout<<endl<<prev_lev_dir<<" DELETED"<<endl;
     
    remove("out_file_dir");
    cout<<"out_file_dir"<<" DELETED"<<endl;
    cout<<endl;

    TIME
    return 0;
}   