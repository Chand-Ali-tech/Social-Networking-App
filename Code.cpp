#include<iostream>
#include <string.h>
#include <fstream>
using namespace std;
class Page;
class User;
class FaceBook;
class Date;
class Activity;
class Object;
class Comment;
class Post;
class Object {
	//char* ID;
public:
	char* ID;
	Object();
};
Object::Object()
{
	ID = new char[10];
}
class Activity {
public:

	int Type;
	char* value;

	Activity();

};
Activity::Activity()
{
	value = new char[25];
	Type = 0;
}
class Date {
public:

	int day;
	int month;
	int year;
	Date(int, int, int);
	Date();
	//static Date CurrentDate;
	//static void SetCurrentDate();
};
Date::Date(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
}
Date::Date()
{
	day = 0;
	month = 0;
	year = 0;
}
class Comment
{
	char* id;
	char* text;
	Object commentBy;
	Object commentOn;
	//User* CommentBy;
	User* commentByUser;
	static int total_comments;
public:
	Comment();
	void DataFromFile(ifstream&,FaceBook&);
	int SearchingCommentsByID(const char*, Comment**, Comment**);
	const char* getText() const { return text; }
	Object GetCommentOn() { return commentOn; }
	Object GetCommentBy() { return commentBy; }
	User* name()
	{
		return commentByUser;
	}
};
int Comment::total_comments = 0;
Comment::Comment()
{
	id = new char[5];
	text = new char[60];
}
void Comment::DataFromFile(ifstream& fin,FaceBook &fb)
{
	total_comments++;
	fin >> id;
	fin >> commentOn.ID;
	fin >> commentBy.ID;

	//commentByUser = fb.FaceBook::SearchUserByID(commentBy.ID);
	//commentByUser = fb.SearchUserByID(commentBy.ID);
	

	fin.getline(text, 60);
	cout << id << "   " << commentOn.ID << "   " << commentBy.ID << "    " << text << endl;
}
int Comment::SearchingCommentsByID(const char* IDOfPost, Comment** commen, Comment** co)
{
	int count = 0;
	for (int i = 0; i < total_comments; i++)
	{
		if (strcmp(IDOfPost, commen[i]->commentOn.ID) == 0)
		{

			//co[i] = &commen[i];
			*co[count] = *commen[i];
			count++;
			//cout << co[count] << " ";
		}
	}
	return count;
}
//-------------- Post -----------------------------------------------------//
class Post {
	//public:
	Activity* activity;
	char* PostID;
	/*Date SharedDate;
	static Date CurrentDate;*/
	char* Text;
	Object* SharedBy;
	Object** LikedBy;
	int liked_count;
	Comment** comments;
	int comment_count;
	int type;
public:
	Post();
	void ReadPostFromFile(ifstream& fin);
	void EveryPostLoadYourComments(Comment**);
	void Liked()
	{
		for (int i = 0; i < liked_count; i++)
		{
			if (LikedBy[i] == NULL) { cout << "NULL"; }
			else
			{
				cout << arr[i] << " = ARR";
			}
		}
		
			

	}
	static void SetCurrent_Date();
	int GetLiked_count()
	{
		return liked_count;
	}
	int GetComment_Count()
	{
		return comment_count;
	}
	Object* GetSharedBy()
	{
		return SharedBy;
	}
	char arr[5][5];
	Date SharedDate;
	int GetType() { return type; }
	static Date CurrentDate;
	Activity* GetActivity()
	{
		return activity;
	}
	char* GetText()
	{
		return Text;
	}Comment** GetComment()
	{
		return comments;
	}
	Object** GetLikedBy()
	{
		return LikedBy;
	}
	char* GetPostID()
	{
		return PostID;
	}
};
//Date Post::CurrentDate = 0;
Date Post::CurrentDate(0,0,0);
void Post::SetCurrent_Date()
{
	CurrentDate.day = 15;
	CurrentDate.month = 11;
	CurrentDate.year = 2017;
}
Post::Post()
{
	PostID = new char[10];
	Text = new char[80];
	/*LikedBy = new Object * [5];
	for (int i = 0; i < 5; i++)
	{
		LikedBy[i] = new Object;
	}*/
}
void Post::ReadPostFromFile(ifstream& fin)
{
	//fin >> Type;
	activity = new Activity;
	fin >> activity->Type;
	fin >> PostID;
	//SharedDate = new Date;--> SharedDate is not pointer.
	fin >> SharedDate.day;
	fin >> SharedDate.month;
	fin >> SharedDate.year;
	Post::SetCurrent_Date();
	fin.ignore();
	fin.getline(Text, 80);
	//cout << "Text:" << Text << endl;
	if (activity->Type == 2)
	{
		//int a;
		//fin >> activity->Type;
		fin >> type;
		//fin >> activity->value;
		fin.getline(activity->value, 25);
	}
	SharedBy = new Object;
	fin >> SharedBy->ID;
	char temp[10][5]; int count = 0;
	for (int i = 0; i < 10; i++)
	{
		fin >> temp[i];
		if (temp[i][0] == '-' && temp[i][1] == '1')
		{
			break;
		}
		else
		{
			count++;
		}
	}
	liked_count = count;
	LikedBy = new Object * [liked_count];
	for (int i = 0; i < liked_count; i++)
	{
		cout << temp[i] << " t";
		LikedBy[i] = new Object;
		LikedBy[i]->ID = temp[i];
		strcpy_s(arr[i], temp[i]);
		//cout << arr;
		//arr[i] = temp[i];
		cout << LikedBy[i]->ID << " ";
	}
	////////////////////////////////////
	cout << activity->Type << endl;
	cout << PostID << endl;
	cout << SharedDate.day << "    ";
	cout << SharedDate.month << "    ";
	cout << SharedDate.year << endl;
	cout << Text << endl;
	if (activity->Type == 2)
	{
		cout << activity->Type << "   ";
		cout << activity->value << endl;
	}
	cout << SharedBy->ID << endl;
	for (int i = 0; i < liked_count; i++)
	{
		//cout<<LikedBy[i]->ID;
		if (LikedBy[i] == NULL) { cout << "NULL"; }
		else
			cout << LikedBy[i]->ID << "  \/  ";
		
	}
	cout << endl;
	//cout << "......................................................\n\n\n";
}
void Post::EveryPostLoadYourComments(Comment** comment)
{
	//Comment com;
	Comment* comm;
	comm = new Comment[10];
	int a;
	comments = new Comment * [5];
	for (int i = 0; i < 5; i++)
	{
		comments[i] = new Comment();
	}
	a = comm->SearchingCommentsByID(PostID, comment, comments);
	comment_count = a;
	for (int i = 0; i < a; i++)
	{
		cout << comments[i]->getText() << endl;
	}
	
}
//--------------  Page  ---------------------------------------------------//
class Page
{
	char* ID;
	char* Title;
	Post** Timeline;
	int post_count = 0;
public:
	Page();
	void ReadDataFromFile(ifstream& fin);
	//void PrintListOfPages();
	char* IDGetter();
	char* TitleGetter();
	//void AddPostToTimeline(Post* post);
};
char* Page::IDGetter()
{
	return ID;
}
char* Page::TitleGetter()
{
	return Title;
}
Page::Page()
{
	ID = new char[5];
	Title = new char[50];
}
void Page::ReadDataFromFile(ifstream& fin)
{
	fin >> ID;
	fin.getline(Title, 50);
}

//void Page::PrintListOfPages()
//{
//	cout << this->ID << "			" << this->Title << endl;
//}
//--------------  User  ---------------------------------------------------//
class User
{
	char* ID;
	char* Fname;
	char* Lname;
	Page** LikedPages;
	User** FriendUser;
	char** friendtemp;
	int friend_count;
	char** pagestemp;
	int pages_count;
	static int total;

	Post** timeline;

public:
	void ReadYourDataUsersLikedPages(ifstream& read);
	void GetYourFriend(User**);
	void GetYourLikedPages(Page**);
	void DeAllocate_Temp_Friends_Pages();
	void ViewFriendList();
	void ViewLikedPages();
	void ViewHome(Post**);
	char* GetUserID();
	char* GetFname()
	{
		return Fname;
	}
	char* GetLname()
	{
		return Lname;
	}
	User();
	void ViewLikedList(const char*,Post**);
	void LikePost(const char*,Post**);
};
void LikePost(const char* arr,Post **pos)
{
	
	for (int i = 0; i < 12; i++)
	{
		if (strcmp(pos[i]->GetPostID(), arr) == 0)
		{
			int l = pos[i]->GetLiked_count();
			for (int i = 0; i < pos[i]->GetLiked_count(); i++)
			{

			}
			break;
		}
	}
}
void User::ViewHome(Post **pos)
{
	cout << "\nCommand:                View Home\n\n";
	cout << "--------------------------------------------------------------------------\n\n";
	cout << Fname << " " << Lname << " - " << "Home\n\n\n";
	int b = 0;
	// 12 = Total Posts
	for (int i = 0; i <12  ;i++)
	{
	/*	cout << pos[i]->CurrentDate.day << " " << pos[i]->SharedDate.day << endl;
		cout << pos[i]->GetActivity()->Type << " " << pos[i]->GetActivity()->value << endl;*/
		bool flag = false;
		if (strcmp(FriendUser[b]->ID,pos[i]->GetSharedBy()->ID)==0 && (pos[i]->CurrentDate.day==pos[i]->SharedDate.day || pos[i]->CurrentDate.day-1 == pos[i]->SharedDate.day))
		{
			if (pos[i]->GetActivity()->Type == 2)
			{
				flag = true;
				if (pos[i]->GetType() == 1)
				{
					cout <<"---"<< FriendUser[b]->Fname << " " << FriendUser[b]->Lname << " is feeling " << pos[i]->GetActivity()->value << endl;
				}
				else if (pos[i]->GetActivity()->Type == 2)
				{
					cout << "---" << FriendUser[b]->Fname << " " << FriendUser[b]->Lname << " is thinking about " << pos[i]->GetActivity()->value << endl;
				}
				else if (pos[i]->GetActivity()->Type == 3)
				{
					cout << "---" << FriendUser[b]->Fname << " " << FriendUser[b]->Lname << " is making " << pos[i]->GetActivity()->value << endl;
				}
				else if (pos[i]->GetActivity()->Type == 4)
				{
					cout << "---" << FriendUser[b]->Fname << " " << FriendUser[b]->Lname << " is celebrating " << pos[i]->GetActivity()->value << endl;
				}
			}
			if (flag == false)
			{
				cout<<"---"<< FriendUser[b]->Fname << " " << FriendUser[b]->Lname << " shared " << endl;
			}
			cout<< pos[i]->GetText() << endl;
			for (int a =0; a < pos[i]->GetComment_Count(); a++)
			{
				char* id;
				id = pos[i]->GetComment()[a]->GetCommentBy().ID;
				cout << "          " << id << " wrote :";
				//cout << id << " ";
				cout << pos[i]->GetComment()[a]->getText() << endl;
			}
			cout << endl;
			b++;
		}
		if (b == friend_count)
		{
			break;
		}
	}
	///// Pages
	int c = 0;
	for (int i = 0; i < 12; i++)
	{
		//int c = 0;
		bool flag = false;
		//cout << LikedPages[c]->IDGetter() << "    " << pos[i]->GetSharedBy()->ID << endl;

		if (strcmp(LikedPages[c]->IDGetter(), pos[i]->GetSharedBy()->ID) == 0 && (pos[i]->CurrentDate.day == pos[i]->SharedDate.day || pos[i]->CurrentDate.day - 1 == pos[i]->SharedDate.day))
		{
			if (pos[i]->GetActivity()->Type == 2)
			{
				flag = true;
				if (pos[i]->GetType() == 1)
				{
					cout << "---" << LikedPages[c]->TitleGetter() << " is feeling " << pos[i]->GetActivity()->value << endl;
				}
				else if (pos[i]->GetActivity()->Type == 2)
				{
					cout << "---" << LikedPages[c]->TitleGetter() << " is thinking about " << pos[i]->GetActivity()->value << endl;
				}
				else if (pos[i]->GetActivity()->Type == 3)
				{
					cout << "---" << LikedPages[c]->TitleGetter() << " is making " << pos[i]->GetActivity()->value << endl;
				}
				else if (pos[i]->GetActivity()->Type == 4)
				{
					cout << "---" << LikedPages[c]->TitleGetter() << " is celebrating " << pos[i]->GetActivity()->value << endl;
				}
			}
			if (flag == false)
			{
				cout << "---" << LikedPages[c]->TitleGetter() << " shared " << endl;
			}
			cout << pos[i]->GetText() << endl;
			for (int a = 0; a < pos[i]->GetComment_Count(); a++)
			{
				char* id;
				id = pos[i]->GetComment()[a]->GetCommentBy().ID;
				cout << "          " << id << " wrote :";
				//cout << id << " ";
				cout << pos[i]->GetComment()[a]->getText() << endl;
			}
			cout << endl;
			c++;
		}
	}
	cout << "--------------------------------------------------------------------------\n\n";
}
void User::ViewLikedList(const char* post, Post **pos)
{
	cout << "Command:                View Post Liked-List\n\n";
	cout << "--------------------------------------------------------------------------\n\n";
	cout << "Post liked by :-\n";
	for (int i = 0; i < 12; i++)
	{
		if (strcmp(pos[i]->GetPostID(),post)==0)
		{
			for (int a = 0; a < pos[i]->GetLiked_count(); a++)
			{
				//cout << pos[i]->GetLikedBy()[a]->ID << endl;
				cout << pos[i]->arr[a] << endl;
			}
		}
	}
	cout << "--------------------------------------------------------------------------\n\n";
}
int User::total = 0;
char* User::GetUserID()
{
	return ID;
}
User::User()
{
	ID = new char[5];
	Fname = new char[20];
	Lname = new char[20];
	LikedPages = NULL;
	FriendUser = NULL;
	friendtemp = NULL;
	pagestemp = NULL;
	friend_count = 0;
	pages_count = 0;
}
void User::ReadYourDataUsersLikedPages(ifstream& read)
{
	read >> this->ID;
	//cout << this->ID<<" ";
	read >> this->Fname;
	//cout << this->Fname << " ";
	read >> this->Lname;
	//cout << this->Lname << " " << endl;

	// Friends
	//cout << total << ":------------\n";
	total++;
	friendtemp = new char* [10];
	for (int i = 0; i < 10; i++)
	{
		friendtemp[i] = new char[5];
	}
	int a = 0;
	while (1)
	{
		read >> friendtemp[a];
		if (friendtemp[a][0] == '-' && friendtemp[a][1] == '1')
		{
			break;
		}
		else
		{
			a++;
		}
	}
	friend_count = a;
	//cout << "Users = " << friend_count << endl;
	// Pages
	a = 0;
	pagestemp = new char* [10];
	for (int i = 0; i < 10; i++)
	{
		pagestemp[i] = new char[5];
	}
	while (1)
	{
		read >> pagestemp[a];
		if (pagestemp[a][0] == '-' && pagestemp[a][1] == '1')
		{
			break;
		}
		else
		{
			a++;
		}
	}
	pages_count = a;
	a = 0;
	//cout << "Pages = " << pages_count << endl;
}
void User::GetYourFriend(User** use)
{
	FriendUser = new User * [friend_count];
	for (int i = 0; i < friend_count; i++)
	{
		FriendUser[i] = NULL;
	}
	int a = 0;
	for (int i = 0; i < User::total; i++)
	{
		if (strcmp(use[i]->ID, friendtemp[a]) == 0)
		{
			FriendUser[a] = use[i];
			a++;
			//cout << "Came  ";
		}
		if (a == friend_count)
		{
			break;
		}
	}
	//cout << endl; cout << "Users ID \n";
	/*for (int i = 0; i < friend_count; i++)
	{
		cout << FriendUser[i]->ID << endl;
	}*/
}

void User::GetYourLikedPages(Page** pag)
{
	LikedPages = new Page * [pages_count];
	for (int i = 0; i < pages_count; i++)
	{
		LikedPages[i] = NULL;
	}
	int a = 0;
	for (int i = 0; i < User::total; i++)
	{
		if (strcmp(pag[i]->IDGetter(), pagestemp[a]) == 0)
		{
			LikedPages[a] = pag[i];
			a++;
			//cout << "Came  ";
		}
		if (a == pages_count)
		{
			break;
		}
	}
	cout << endl;
	/*cout << "PAges:\n";
	for (int i = 0; i < pages_count; i++)
	{
		cout << LikedPages[i]->IDGetter() << endl;
	}*/
}

void User::DeAllocate_Temp_Friends_Pages() {


	for (int i = 0; i < friend_count; i++)
	{
		//cout << "Deallocate : " << this->ID << endl;
		delete[] friendtemp[i];
	}
	delete friendtemp;
	friendtemp = NULL;
	for (int i = 0; i < pages_count; i++)
	{
		//cout << "Deallocate : " << this->pagestemp[i] << endl;
		delete[] pagestemp[i];
	}
	delete[] pagestemp;
	pagestemp = NULL;
}
void User::ViewFriendList()
{

	//cout << this->Fname << " " << this->Lname << "  successfully set as current user\n";
	cout << "Command:                View Friend List\n";
	cout << "--------------------------------------------------------------------------\n";
	cout << this->Fname << " " << this->Lname << " - FriendList\n\n";
	if (friend_count != 0) {
		for (int i = 0; i < friend_count; i++)
		{
			cout << FriendUser[i]->ID << "-" << FriendUser[i]->Fname << " " << FriendUser[i]->Lname << endl;
		}
	}
	else
	{
		cout << "No Friend ! \n";
	}
	cout << "--------------------------------------------------------------------------\n\n";
}
void User::ViewLikedPages()
{
	cout << "Command:                View Liked Pages\n\n";
	cout << "--------------------------------------------------------------------------\n";
	cout << this->Fname << " " << this->Lname << " - LikedPages\n\n";
	if (pages_count != 0) {
		for (int i = 0; i < pages_count; i++)
		{
			cout << LikedPages[i]->IDGetter() << " - " << LikedPages[i]->TitleGetter() << endl;
		}
	}
	else
	{
		cout << "No Liked Pages !\n";
	}
	cout << "--------------------------------------------------------------------------\n";
}
//--------------  FaceBook  ---------------------------------------------------//
class FaceBook
{
	Page** pages;
	User** users;
	Post** posts;
	Comment** comments;
public:
	FaceBook();
	void LoadPagesFromFile(ifstream& fin);
	void LoadUsersFromFile(ifstream& read);
	User* SearchUserByID(const char*);
	void LinkingTheIDs();
	static int TotalPages;
	static int TotalUsers;
	static int UsersGetter();

	void LoadData(ifstream& fin, ifstream& read,FaceBook);
	void LoadPost(ifstream& fin);
	void LoadComment(ifstream& fin,FaceBook);
	//void ViewHome(Post **posts,Comment**comments);
	void ShowEverything(Comment**,Post**);
	Post** PostGetter()
	{
		return posts;
	}
	Comment** CommentGetter()
	{
		return comments;
	}
};
int FaceBook::TotalPages = 0;
int FaceBook::TotalUsers = 0;
FaceBook::FaceBook()
{
	pages = NULL;
	users = NULL;
	posts = nullptr;
	comments = nullptr;
}
int FaceBook::UsersGetter()
{
	return TotalUsers;
}
User* FaceBook::SearchUserByID(const char* arr)
{
	for (int i = 0; i < TotalUsers; i++)
	{
		if (strcmp(users[i]->GetUserID(), arr) == 0)
		{
			return users[i];
		}
	}
	return NULL;
}
void FaceBook::LoadPagesFromFile(ifstream& fin)
{
	fin >> TotalPages;
	pages = new Page * [TotalPages];
	for (int i = 0; i < TotalPages; i++)
	{
		pages[i] = new Page;
		pages[i]->ReadDataFromFile(fin);
		//pages[i]->PrintListOfPages();
	}
	fin.close();
}
void FaceBook::LoadUsersFromFile(ifstream& read)
{
	read >> TotalUsers;
	users = new User * [TotalUsers];
	for (int i = 0; i < TotalUsers; i++)
	{
		users[i] = new User;
	}
	for (int i = 0; i < TotalUsers; i++)
	{
		users[i]->ReadYourDataUsersLikedPages(read);
	}
	read.close();
}
void FaceBook::LinkingTheIDs()
{
	for (int i = 0; i < TotalUsers; i++)
	{
		users[i]->GetYourFriend(users);
	}
	cout << "-----------------------------------------------\n";
	for (int i = 0; i < TotalUsers; i++)
	{
		users[i]->GetYourLikedPages(pages);
	}
	for (int i = 0; i < TotalUsers; i++)
	{
		users[i]->DeAllocate_Temp_Friends_Pages();
	}
}
void FaceBook::LoadData(ifstream& fin, ifstream& read,FaceBook fb)
{
	LoadComment(read,fb);
	LoadPost(fin);
	//LoadComment(read);
}
void FaceBook::LoadPost(ifstream& fin)
{
	int total;
	fin >> total;
	posts = new Post * [total];
	for (int i = 0; i < total; i++)
	{
		posts[i] = new Post;
	}
	for (int i = 0; i < total; i++)
	{
		posts[i]->ReadPostFromFile(fin);
		posts[i]->Liked();
		posts[i]->EveryPostLoadYourComments(comments);
		/*posts[i]->Liked();*/
	}
}
void FaceBook::LoadComment(ifstream& fin,FaceBook fb)
{
	int total;
	fin >> total;
	comments = new Comment * [total];
	for (int i = 0; i < total; i++)
	{
		comments[i] = new Comment();
	}
	for (int i = 0; i < total; i++)
	{
		comments[i]->DataFromFile(fin,fb);
	}
}
void FaceBook::ShowEverything(Comment** comm,Post** pos)
{
	User* Currentuser = SearchUserByID("u7");
	if (Currentuser != NULL)
	{
		cout << Currentuser->GetFname()<<" "<<Currentuser->GetLname() << " successfully set as Current User\n";
		Currentuser->ViewFriendList();
		Currentuser->ViewLikedPages();
		Currentuser->ViewHome(pos);
		Currentuser->ViewLikedList("post5",pos);
		Currentuser->LikePost("post5", pos);
	}
	else
		cout << "User not found!\n";
}
///////////-----  MAIN  ----///////
int main()
{
	ifstream read("pages.txt");
	ifstream fin("users.txt");
	ifstream post("posts.txt");
	ifstream comment("comments.txt");
	if (read.is_open() && fin.is_open() && post.is_open() && comment.is_open())
	{
		FaceBook FB;
		FB.LoadPagesFromFile(read);
		FB.LoadUsersFromFile(fin);
		FB.LinkingTheIDs();
		FB.LoadData(post, comment,FB);
		//FB.ShowEverything(FB.CommentGetter(),FB.PostGetter());
	}
	else
	{
		cout << "Pages or users or posts or comments file not found ! \n";
	}
	return 0;
}