#include "Dictionary.h"
int
main () {
 
    const int tableSize = 37;	// set to 101 in assignment description

    char *sites[] =  {
	"accuweather.com",
	"alipay.com",
	"amazon.com",
	"baidu.com",
	"bing.com",
	"csdn.net",
	"ebay.com",
	"facebook.com",
	"google.com",
	"google.com.ar",
	"google.com.au",
	"google.com.br",
	"google.ca",
	"google.fr",
	"google.de",
	"google.com.hk",
	"google.co.in",
	"google.co.id",
	"google.it",
	"google.co.jp",
	"google.pl",
	"google.ru",
	"google.es",
	"google.co.th",
	"google.com.tr",
	"google.co.uk",
	"goo.gl",
	"googleweblight.com",
	"360.cn",
	"instagram.com",
	"jd.com",
	"linkedin.com",
	"mail.ru",
	"microsoft.com",
	"office.com",
	"msn.com",
	"Naver.com",
	"netflix.com",
	"ok.ru",
	"reddit.com",
	"samsung.com",
	"sm.cn",
	"sina.com.cn",
	"weibo.com",
	"sogou.com",
	"sohu.com",
	"spotify.com",
	"t.co",
	"taobao.com",
	"qq.com",
	"tmall.com",
	"pages.tmall.com",
	"list.tmall.com",
	"twitch.tv",
	"twitter.com",
	"vk.com",
	"whatsapp.com",
	"wikipedia.org",
	"live.com",
	"yahoo.com",
	"yahoo.co.jp",
	"youtube.co"};



    HashTableObj  *H;
    int i;
	H = newHashTable(tableSize);

    for (i=0; i< 62; i++) {
        insert(H, sites[i]);
    }
    printHashTable(stdout, H);
    deleteHashTable(H);
}

