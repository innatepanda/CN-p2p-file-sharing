#define HASHMAP_MAX_SIZE 50

struct connection
{
 	struct sockaddr_in client;
 	int id;

};
struct peer_dets
{
	int fd;
	char filepath[50];
	
};
struct clientinfo
{
	char username[50];
	char password[50];

	//char filename[50];
	int status; // 1-online  0-offline 
	
};

//TODO: for hashmap, array of struct client_server
struct clientinfo_server
{
	char username[50];
	char password[50];
	int status; 
	time_t date[50]; //at time of reg, server assigns
	
};
struct hashmap_details{

	int max_size;
	int cur_size;
	
} hashmap_default = {HASHMAP_MAX_SIZE, 1};
 
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

