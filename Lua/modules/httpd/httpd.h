

#ifndef _HTTPD_H
#define _HTTPD_H

#include <spiffs.h>
#include <esp_spiffs.h>




#define IN_BUF_LEN  400 //512
#define OUT_BUF_LEN  312 //256 //312  //536 //312
//512

#undef MAXPATHLEN
#define MAXPATHLEN  55 //32 //55 
//PATH_MAX



#define DEF_RECV_TIMEOUT  100
#define DEF_SEND_TIMEOUT  60000


#define WS_TIMEOUT_NO_RECONNECT		10
#define WS_TIMEOUT_UNCONNECT		300



#ifndef ERR_IS_FATAL
#define ERR_IS_FATAL(e) (e < ERR_ISCONN)
#endif


typedef struct _get_par get_par;

struct _get_par {
	char *name;
	char *val;
	
	get_par* next;
};



typedef struct {
	const char* suf;
	const char* hdr;
	const char* siz;
} suf_hdr;




int check_conn(char* fn, int ln);
err_t print_err(err_t err);

void ws_sock_del();
void ws_task(lua_State *L);
int do_websock(char **uri, int uri_len, char *hdr, char* hdr_sz, char* data, int len, char *out, char *suff );

int get_list_add(get_par** first, char* name, char* val);
void get_list_free(get_par** first);
int lget_params_cnt(lua_State* L);
int lget_param(lua_State* L);

char* suf_to_hdr(char* suf, int suf_len, char** siz);

int get_uri(char* in, int in_len, char** uri, char** suf, int* suf_len, get_par** ppget_root);
spiffs_file uri_to_file(char* uri, int len, int *flen);



extern int is_httpd_run;

extern get_par* get_root;

extern spiffs fs;

#endif

