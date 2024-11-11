#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>

using namespace std;

class Course_Reference {
	public:
		int id;
		int cour_id;
		string cour_ref_code;
		string book_title;
		string book_author;
		string book_details;
};

int course_reference_count = 0;
vector<Course_Reference> course_references;

const char* FILE_NAME =  "course_reference_setting.txt";

void power_rangers_course_reference_create();
void power_rangers_course_reference_update();
void power_rangers_course_reference_retrive();
void power_rangers_course_reference_delete();
void power_rangers_course_reference_storing();
void power_rangers_course_reference_sort_by_ref_code();
void power_rangers_course_reference_search_by_ref_code();

void power_rangers_course_reference_complexity_search(){
	cout<<"Time Complexity analysis:"<<endl;
	cout<<"Linear Search: O(n)"<<endl;
	cout<<"Binary Search: O(logn)"<<endl;
}

void power_rangers_course_reference_complexity_sorting(){
	cout<<"Time Complexity analysis:"<<endl;
	cout<<"Insertion Sort: O(n)"<<endl;
	cout<<"Selection Sort: O(n)"<<endl;
}

void load_from_file() {
	ifstream file(FILE_NAME);
	
	if(!file.is_open()) {
		cerr<<"Failed to open file: "<<FILE_NAME<<endl;
		return;
	}
	
	Course_Reference course_ref;
	while(file >> course_ref.id >> course_ref.cour_id) {
		file.ignore(); 
		getline(file, course_ref.cour_ref_code);
        getline(file, course_ref.book_title);
        getline(file, course_ref.book_author);
        getline(file, course_ref.book_details);

        course_references.push_back(course_ref);
        course_reference_count++;	
    }
    file.close();
}

void power_rangers_course_reference_storing() {
	ofstream file(FILE_NAME, ios::out | ios::trunc);
	
	if(!file.is_open()) {
		cerr<<"Failed to open file: "<<FILE_NAME<<endl;
		return;
	}
	
	for(int i = 0;i < course_references.size();i++) {
		file << course_references[i].id << " "
		     << course_references[i].cour_id << "\n"
		     << course_references[i].cour_ref_code << "\n"
		     << course_references[i].book_title << "\n"
		     << course_references[i].book_author << "\n"
		     << course_references[i].book_details << "\n";
	}
	file.close();
}

void power_rangers_course_reference_create() {
	Course_Reference c;
	cout<<"Enter ID: ";
	cin>>c.id;
	cout<<"Enter Course ID: ";
	cin>>c.cour_id;
	cin.ignore();
	cout<<"Enter Course Reference Code: ";
	getline(cin,c.cour_ref_code);
	cout<<"Enter Book Title: ";
	getline(cin,c.book_title);
	cout<<"Enter Book Author: ";
	getline(cin,c.book_author);
	cout<<"Enter Book Details: ";
	getline(cin,c.book_details);
	
	course_reference_count++;
	course_references.push_back(c);
	power_rangers_course_reference_storing();
	cout<<"Course Reference created successfully!"<<endl;
}

void power_rangers_course_reference_update() {
	int id;
	cout<<"Enter ID to update: ";
	cin>>id;
	bool found = false;
	for(int i = 0;i < course_references.size();i++){
		if(course_references[i].id == id){
			cout<<"Enter new ID: ";
	        cin>>course_references[i].id;
			cout<<"Enter new Course ID: ";
	        cin>>course_references[i].cour_id;
	        cin.ignore();
			cout<<"Enter new Course Reference Code: ";
			getline(cin,course_references[i].cour_ref_code);
			cout<<"Enter new Book Title: ";
			getline(cin,course_references[i].book_title);
			cout<<"Enter new Book Author: ";
			getline(cin,course_references[i].book_author);
			cout<<"Enter new Book Details: ";
			getline(cin,course_references[i].book_details);
		 	power_rangers_course_reference_storing();
			cout<<"Course Reference updated successfully!"<<endl;
			found = true;
			break;
		}
	}
	if(!found) cout<<"Course Reference with ID "<<id<<" not found!"<<endl;
}

void power_rangers_course_reference_retrieve() {
	cout << "\n\t\t\t\t\tList of Course References" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;

    if (course_references.size() <= 0) {
        cout << "No Course References found!" << endl;
        return;
    }

    cout << left << setw(10) << "ID" 
         << setw(15) << "Course ID" 
         << setw(20) << "Reference Code" 
         << setw(25) << "Book Title" 
         << setw(20) << "Author" 
         << "Details" << endl;
    
    cout << "----------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < course_references.size(); i++) {
        cout << left << setw(10) << course_references[i].id
             << setw(15) << course_references[i].cour_id
             << setw(20) << course_references[i].cour_ref_code
             << setw(25) << course_references[i].book_title
             << setw(20) << course_references[i].book_author
             << course_references[i].book_details << endl;
    }
}

void power_rangers_course_reference_delete() {
	int id;
	cout<<"Enter ID to delete: ";
	cin>>id;
	bool found = false;
	for(int i = 0;i < course_references.size();i++) {
		if(course_references[i].id == id) {
			course_references.erase(course_references.begin()+i);
			course_reference_count--;
		 	found = true;
			cout<<"Course Reference deleted successfully!"<<endl;
			break;
		}
	}
	if(found) power_rangers_course_reference_storing();
	else cout<<"Course Reference with ID "<<id<<" not found!"<<endl; 
}

void power_rangers_course_reference_insertion_sort() {
    int sort_by;
    cout << "Sort Course References by:\n";
    cout << "1. Course ID\n";
    cout << "2. Course Reference Code\n";
    cout << "3. Book Title\n";
    cout << "Enter your choice (1/2/3): ";
    cin >> sort_by;
    cout<<"Sorted using Insertion Sort: "<<endl;
    for (int i = 1; i < course_references.size(); i++) {
        Course_Reference temp = course_references[i];
        int j = i - 1;
        
        while (j >= 0 && 
               ((sort_by == 1 && course_references[j].cour_id > temp.cour_id) ||
                (sort_by == 2 && course_references[j].cour_ref_code > temp.cour_ref_code) ||
                (sort_by == 3 && course_references[j].book_title > temp.book_title))) {
            course_references[j + 1] = course_references[j];
            j--;
        }
        course_references[j + 1] = temp;
    }
    
    if (sort_by == 1) {
        cout << "Course References sorted by ID." << endl;
    } else if (sort_by == 2) {
        cout << "Course References sorted by Course ID." << endl;
    } else if (sort_by == 3) {
        cout << "Course References sorted by Book Title." << endl;
    } else {
        cout << "Invalid Choice." << endl;
        return;
    }

    power_rangers_course_reference_storing();
    power_rangers_course_reference_retrieve();
}

void power_rangers_course_reference_compare_sorting_selection_sort() {
    int sort_by;
    cout << "Sort Course References by:\n";
    cout << "1. Course ID\n";
    cout << "2. Course Reference Code\n";
    cout << "3. Book Title\n";
    cout << "Enter your choice (1/2/3): ";
    cin >> sort_by;
    cout<<"Sorted using Insertion Sort: "<<endl;
    
    for (int i = 0; i < course_references.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < course_references.size(); j++) {
            if ((sort_by == 1 && course_references[j].cour_id < course_references[minIndex].cour_id) ||
                (sort_by == 2 && course_references[j].cour_ref_code < course_references[minIndex].cour_ref_code) ||
                (sort_by == 3 && course_references[j].book_title < course_references[minIndex].book_title)) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            swap(course_references[i], course_references[minIndex]);
        }
    }
    
    if (sort_by == 1) {
        cout << "Course References sorted by ID." << endl;
    } else if (sort_by == 2) {
        cout << "Course References sorted by Course ID." << endl;
    } else if (sort_by == 3) {
        cout << "Course References sorted by Book Title." << endl;
    } else {
        cout << "Invalid Choice." << endl;
        return;
    }


    power_rangers_course_reference_storing();
    power_rangers_course_reference_retrieve();
}

void power_rangers_course_reference_insertion_sort_details(){
	cout<<"for i = 1 to n-1"<<endl;
    cout<<"key = array[i]"<<endl;
    cout<<"j = i - 1"<<endl;
    cout<<"while j >= 0 and array[j] > key"<<endl;
        cout<<"array[j + 1] = array[j]"<<endl;
        cout<<"j = j - 1"<<endl;
        cout<<"array[j + 1] = key"<<endl;
}

void power_rangers_course_reference_linear_search_details(){
	cout<<"function linearSearch(array, target):"<<endl;
    cout<<"for i = 0 to array.length - 1"<<endl;
        cout<<"if array[i] == target"<<endl;
            cout<<"return i"<<endl;  
    cout<<"return -1 " ;

}

void power_rangers_course_reference_linear_search() {
    int choice;
    cout << "Choose attribute to search by:\n";
    cout << "1) Course ID\n";
    cout << "2) Course Reference Code\n";
    cout << "3) Book Title\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    bool found = false;
    
    switch (choice) {
        case 1: {
            int search_cour_id;
            cout << "Enter Course ID to search: ";
            cin >> search_cour_id;
            for (int i = 0; i < course_references.size(); i++) {
                if (course_references[i].cour_id == search_cour_id) {
                    cout << "ID : " << course_references[i].id << endl;
                    cout << "Course ID : " << course_references[i].cour_id << endl;
                    cout << "Course Reference Code : " << course_references[i].cour_ref_code << endl;
                    cout << "Book Title : " << course_references[i].book_title << endl;
                    cout << "Book Author : " << course_references[i].book_author << endl;
                    cout << "Book Details : " << course_references[i].book_details << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Course Reference with Course ID " << search_cour_id << " not found!" << endl;
            break;
        }
        case 2: {
            string search_ref_code;
            cout << "Enter Course Reference Code to search: ";
            getline(cin, search_ref_code);
            for (int i = 0; i < course_references.size(); i++) {
                if (course_references[i].cour_ref_code == search_ref_code) {
                    cout << "ID : " << course_references[i].id << endl;
                    cout << "Course ID : " << course_references[i].cour_id << endl;
                    cout << "Course Reference Code : " << course_references[i].cour_ref_code << endl;
                    cout << "Book Title : " << course_references[i].book_title << endl;
                    cout << "Book Author : " << course_references[i].book_author << endl;
                    cout << "Book Details : " << course_references[i].book_details << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Course Reference with Code " << search_ref_code << " not found!" << endl;
            break;
        }
        case 3: {
            string search_title;
            cout << "Enter Book Title to search: ";
            getline(cin, search_title);
            for (int i = 0; i < course_references.size(); i++) {
                if (course_references[i].book_title == search_title) {
                    cout << "ID : " << course_references[i].id << endl;
                    cout << "Course ID : " << course_references[i].cour_id << endl;
                    cout << "Course Reference Code : " << course_references[i].cour_ref_code << endl;
                    cout << "Book Title : " << course_references[i].book_title << endl;
                    cout << "Book Author : " << course_references[i].book_author << endl;
                    cout << "Book Details : " << course_references[i].book_details << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Course Reference with Book Title \"" << search_title << "\" not found!" << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
}

void power_rangers_course_reference_compare_search_binary_search() {
    int choice;
    cout << "Choose attribute to search by:\n";
    cout << "1) Course ID\n";
    cout << "2) Course Reference Code\n";
    cout << "3) Book Title\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    bool found = false;

    switch (choice) {
        case 1: {  
            for (int i = 1; i < course_references.size(); i++) {
                Course_Reference temp = course_references[i];
                int j = i - 1;
                while (j >= 0 && course_references[j].cour_id > temp.cour_id) {
                    course_references[j + 1] = course_references[j];
                    j--;
                }
                course_references[j + 1] = temp;
            }

            int search_id;
            cout << "Enter Course ID to search: ";
            cin >> search_id;
            int left = 0, right = course_references.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (course_references[mid].cour_id == search_id) {
                    cout << "ID: " << course_references[mid].id << endl;
                    cout << "Course ID: " << course_references[mid].cour_id << endl;
                    cout << "Course Reference Code: " << course_references[mid].cour_ref_code << endl;
                    cout << "Book Title: " << course_references[mid].book_title << endl;
                    cout << "Book Author: " << course_references[mid].book_author << endl;
                    cout << "Book Details: " << course_references[mid].book_details << endl;
                    found = true;
                    break;
                } else if (course_references[mid].cour_id < search_id) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            break;
        }

        case 2: {  
            for (int i = 1; i < course_references.size(); i++) {
                Course_Reference temp = course_references[i];
                int j = i - 1;
                while (j >= 0 && course_references[j].cour_ref_code > temp.cour_ref_code) {
                    course_references[j + 1] = course_references[j];
                    j--;
                }
                course_references[j + 1] = temp;
            }

            string search_code;
            cout << "Enter Course Reference Code to search: ";
            getline(cin, search_code);
            int left = 0, right = course_references.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (course_references[mid].cour_ref_code == search_code) {
                    cout << "ID: " << course_references[mid].id << endl;
                    cout << "Course ID: " << course_references[mid].cour_id << endl;
                    cout << "Course Reference Code: " << course_references[mid].cour_ref_code << endl;
                    cout << "Book Title: " << course_references[mid].book_title << endl;
                    cout << "Book Author: " << course_references[mid].book_author << endl;
                    cout << "Book Details: " << course_references[mid].book_details << endl;
                    found = true;
                    break;
                } else if (course_references[mid].cour_ref_code < search_code) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            break;
        }

        case 3: {  
            for (int i = 1; i < course_references.size(); i++) {
                Course_Reference temp = course_references[i];
                int j = i - 1;
                while (j >= 0 && course_references[j].book_title > temp.book_title) {
                    course_references[j + 1] = course_references[j];
                    j--;
                }
                course_references[j + 1] = temp;
            }

            string search_title;
            cout << "Enter Book Title to search: ";
            getline(cin, search_title);
            int left = 0, right = course_references.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (course_references[mid].book_title == search_title) {
                    cout << "ID: " << course_references[mid].id << endl;
                    cout << "Course ID: " << course_references[mid].cour_id << endl;
                    cout << "Course Reference Code: " << course_references[mid].cour_ref_code << endl;
                    cout << "Book Title: " << course_references[mid].book_title << endl;
                    cout << "Book Author: " << course_references[mid].book_author << endl;
                    cout << "Book Details: " << course_references[mid].book_details << endl;
                    found = true;
                    break;
                } else if (course_references[mid].book_title < search_title) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            break;
        }

        default:
            cout << "Invalid choice!" << endl;
            return;
    }

    if (!found) {
        cout << "Course Reference not found with the specified attribute!" << endl;
    }
}

int main() {
	load_from_file();
	int choice;
	
	while(1) {
		cout<<"\n1)Create Course Reference\n2)Update Course Reference\n3)Retrieve Course References\n4)Delete Course Reference\n5)Linear Search by Course Reference Code\n6)Insertion Sort by Course Reference Code\n7)Display Complexity for searching\n8)Selection Sort by Course Reference Code\n9)Binary Search by Course Reference Code\n10)Display Complexity for sorting\n11)pseudocode for linear search\n12)pseudocode for Insertion sort\n13)Exit \n";
		cout<<"Enter your choice : ";
		cin>>choice;
		switch(choice) {
			case 1:
			 power_rangers_course_reference_create();
				break;
			case 2:
			 	power_rangers_course_reference_update();
				break;
			case 3:
			 	power_rangers_course_reference_retrieve();
				break;
			case 4:
			 	power_rangers_course_reference_delete();
				break;
			case 5:
			 	power_rangers_course_reference_linear_search();
				break;
			case 6:
			 	power_rangers_course_reference_insertion_sort();
				break;
			case 7:
				power_rangers_course_reference_complexity_search();
				break;
			case 8:
                power_rangers_course_reference_compare_sorting_selection_sort();
                break;
            case 9:
                power_rangers_course_reference_compare_search_binary_search();
                break;
            case 10:
            	power_rangers_course_reference_complexity_sorting();
            	break;
            case 11:
            	power_rangers_course_reference_linear_search_details();
            	break;
            case 12:
            	power_rangers_course_reference_insertion_sort_details();
            	break;
	    case 13:  
		exit(0);
	    default:
		cout<<"Invalid Choice\n";
	}
	}
	return 0;
}
