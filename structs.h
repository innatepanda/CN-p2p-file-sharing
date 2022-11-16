struct connection
{
 	struct sockaddr_in client;
 	int id;

};
struct clientinfo
{
	char username[50];
	char password[50];

	char filename[50];
	int status; // 1-online  0-offline 
	
};

struct clientinfo_server
{
	char username[50];
	char password[50];
	time_t date[50]; //at time of reg, server assigns
	
};

struct signup
{
	char username[50];
	char password[50];
	char filename[50]; 
	int filenum;
	
};

struct login
{
	char username[50];
	char password[50];
};


struct fileinfo //to write in database, prev struct + incoming struct, then write
{
	char username[50];
	char filename[50][50];
	char filepath[50][50];
	int filesize[50];
	int filenum;
	int status;
	
};
