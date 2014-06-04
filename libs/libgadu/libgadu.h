/* include/libgadu.h.  Generated from libgadu.h.in by configure.  */
/* $Id$ */

/*
 *  (C) Copyright 2001-2009 Wojtek Kaniewski <wojtekka@irc.pl>
 *                          Robert J. WoÄąĹźny <speedy@ziew.org>
 *                          Arkadiusz MiÄąâ€şkiewicz <arekm@pld-linux.org>
 *                          Tomasz ChiliÄąâ€žski <chilek@chilan.com>
 *                          Piotr Wysocki <wysek@linux.bydg.org>
 *                          Dawid Jarosz <dawjar@poczta.onet.pl>
 *                          Jakub Zawadzki <darkjames@darkjames.ath.cx>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License Version
 *  2.1 as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307,
 *  USA.
 */

/**
 * \file libgadu.h
 *
 * \brief GÄąâ€šÄ‚Ĺ‚wny plik nagÄąâ€šÄ‚Ĺ‚wkowy biblioteki
 */

#ifndef LIBGADU_LIBGADU_H
#define LIBGADU_LIBGADU_H

#ifdef _WIN32
#pragma pack(push, 1)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <stdio.h>
#include <stdarg.h>

/** \cond ignore */

/* Defined if libgadu was compiled for bigendian machine. */
/* #undef GG_CONFIG_BIGENDIAN */

/* Defined if this machine has gethostbyname_r(). */
/* #undef GG_CONFIG_HAVE_GETHOSTBYNAME_R */

/* Defined if libgadu was compiled and linked with fork support. */
/* #undef GG_CONFIG_HAVE_FORK */

/* Defined if libgadu was compiled and linked with pthread support. */
/* #undef GG_CONFIG_HAVE_PTHREAD */

/* Defined if pthread resolver is the default one. */
/* #undef GG_CONFIG_PTHREAD_DEFAULT */

/* Defined if this machine has C99-compiliant vsnprintf(). */
#define GG_CONFIG_HAVE_C99_VSNPRINTF /**/

/* Defined if this machine has va_copy(). */
#define GG_CONFIG_HAVE_VA_COPY /**/

/* Defined if this machine has __va_copy(). */
#define GG_CONFIG_HAVE___VA_COPY /**/

/* Defined if this machine supports long long. */
#define GG_CONFIG_HAVE_LONG_LONG /**/

/* Defined if libgadu was compiled and linked with GnuTLS support. */
/* #undef GG_CONFIG_HAVE_GNUTLS */

/* Defined if libgadu was compiled and linked with OpenSSL support. */
/* #undef GG_CONFIG_HAVE_OPENSSL */

/* Defined if libgadu was compiled and linked with zlib support. */
/* #undef GG_CONFIG_HAVE_ZLIB */

/* Defined if uintX_t types are defined in <stdint.h>. */
/* #undef GG_CONFIG_HAVE_STDINT_H */

/* Defined if uintX_t types are defined in <inttypes.h>. */
#define GG_CONFIG_HAVE_INTTYPES_H /**/

/* Defined if uintX_t types are defined in <sys/inttypes.h>. */
/* #undef GG_CONFIG_HAVE_SYS_INTTYPES_H */

/* Defined if uintX_t types are defined in <sys/int_types.h>. */
/* #undef GG_CONFIG_HAVE_SYS_INT_TYPES_H */

/* Defined if uintX_t types are defined in <sys/types.h>. */
/* #undef GG_CONFIG_HAVE_SYS_TYPES_H */

/* Defined if this machine has uint64_t. */
#define GG_CONFIG_HAVE_UINT64_T /**/

/* Defined if libgadu is GPL compliant (was not linked with OpenSSL or any
   other non-GPL compliant library support). */
#define GG_CONFIG_IS_GPL_COMPLIANT /**/

#ifdef GG_CONFIG_HAVE_OPENSSL
#include <openssl/ssl.h>
#endif

#ifdef GG_CONFIG_HAVE_STDINT_H
#include <stdint.h>
#else
#  ifdef GG_CONFIG_HAVE_INTTYPES_H
#  include <inttypes.h>
#  else
#    ifdef GG_CONFIG_HAVE_SYS_INTTYPES_H
#    include <sys/inttypes.h>
#    else
#      ifdef GG_CONFIG_HAVE_SYS_INT_TYPES_H
#      include <sys/int_types.h>
#      else
#        ifdef GG_CONFIG_HAVE_SYS_TYPES_H
#        include <sys/types.h>
#        else

/* ISO C 9X: 7.18 Integer types <stdint.h> */

typedef unsigned char   uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

#        endif
#      endif
#    endif
#  endif
#endif

#ifndef GG_CONFIG_HAVE_UINT64_T
typedef unsigned long long uint64_t;
#endif

#ifdef _MSC_VER
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#if defined(__GNUC__) && (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4))
#  define GG_GNUC_PRINTF(format_idx, arg_idx) \
	 __attribute__((format (printf, (format_idx), (arg_idx))))
#else
#  define GG_GNUC_PRINTF(format_idx, arg_idx)
#endif

/** \endcond */

/**
 * Numer Gadu-Gadu.
 */
typedef uint32_t uin_t;

/**
 * Identyfikator poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego Gadu-Gadu 7.x.
 */
typedef struct {
	uint8_t id[8];
} gg_dcc7_id_t;

/**
 * Identyfikator sesji multilogowania.
 */
typedef struct {
	uint8_t id[8];
} gg_multilogon_id_t;

/**
 * Makro deklarujĂ„â€¦ce pola wspÄ‚Ĺ‚lne dla struktur sesji.
 */
#define gg_common_head(x) \
	int fd;			/**< Obserwowany deskryptor */ \
	int check;		/**< Informacja o ÄąÄ˝Ă„â€¦daniu odczytu/zapisu (patrz \ref gg_check_t) */ \
	int state;		/**< Aktualny stan poÄąâ€šĂ„â€¦czenia (patrz \ref gg_state_t) */ \
	int error;		/**< Kod bÄąâ€šĂ„â„˘du dla \c GG_STATE_ERROR (patrz \ref gg_error_t) */ \
	int type;		/**< Rodzaj sesji (patrz \ref gg_session_t) */ \
	int id;			/**< Identyfikator sesji */ \
	int timeout;		/**< Czas pozostaÄąâ€šy do zakoÄąâ€žczenia stanu */ \
	int (*callback)(x*); 	/**< Funkcja zwrotna */ \
	void (*destroy)(x*); 	/**< Funkcja zwalniania zasobÄ‚Ĺ‚w */

/**
 * Struktura wspÄ‚Ĺ‚lna dla wszystkich sesji i poÄąâ€šĂ„â€¦czeÄąâ€ž. Pozwala na proste
 * rzutowanie niezaleÄąÄ˝ne od rodzaju poÄąâ€šĂ„â€¦czenia.
 */
struct gg_common {
	gg_common_head(struct gg_common)
};

struct gg_image_queue;

struct gg_dcc7;

struct gg_dcc7_relay;

struct gg_session_private;

/**
 * SposÄ‚Ĺ‚b rozwiĂ„â€¦zywania nazw serwerÄ‚Ĺ‚w.
 */
typedef enum {
	GG_RESOLVER_DEFAULT = 0,	/**< DomyÄąâ€şlny sposÄ‚Ĺ‚b rozwiĂ„â€¦zywania nazw (jeden z poniÄąÄ˝szych) */
	GG_RESOLVER_FORK,		/**< RozwiĂ„â€¦zywanie nazw bazujĂ„â€¦ce na procesach */
	GG_RESOLVER_PTHREAD,		/**< RozwiĂ„â€¦zywanie nazw bazujĂ„â€¦ce na wĂ„â€¦tkach */
	GG_RESOLVER_CUSTOM,		/**< Funkcje rozwiĂ„â€¦zywania nazw dostarczone przed aplikacjĂ„â„˘ */
	GG_RESOLVER_WIN32,		/**< RozwiĂ„â€¦zywanie nazw bazujĂ„â€¦ce na wĂ„â€¦tkach Win32 */
	GG_RESOLVER_INVALID = -1	/**< NieprawidÄąâ€šowy sposÄ‚Ĺ‚b rozwiĂ„â€¦zywania nazw (wynik \c gg_session_get_resolver) */
} gg_resolver_t;

/**
 * Rodzaj kodowania znakÄ‚Ĺ‚w.
 */
typedef enum {
	GG_ENCODING_CP1250 = 0,		/**< Kodowanie CP1250 */
	GG_ENCODING_UTF8,		/**< Kodowanie UTF-8 */
	GG_ENCODING_INVALID = -1	/**< NieprawidÄąâ€šowe kodowanie */
} gg_encoding_t;

/**
 * StopieÄąâ€ž kompatybilnoÄąâ€şci ze starymi wersjami API.
 */
typedef enum {
	GG_COMPAT_LEGACY = 0,	/**< CaÄąâ€škowita kompatybilnoÄąâ€şĂ„â€ˇ (nie wyÄąâ€šĂ„â€¦cza ÄąÄ˝adnych funkcji) */
	GG_COMPAT_1_12_0 = 1	/**< WyÄąâ€šĂ„â€¦cza: dostarczanie eventÄ‚Ĺ‚w GG_EVENT_ACK, stary format konferencji */
} gg_compat_t;

/**
 * Flaga poÄąâ€šĂ„â€¦czenia szyfrowanego.
 *
 * \ingroup login
 */
typedef enum {
	GG_SSL_DISABLED = 0,	/**< PoÄąâ€šĂ„â€¦czenie SSL wyÄąâ€šĂ„â€¦czone */
	GG_SSL_ENABLED,		/**< PoÄąâ€šĂ„â€¦czenie SSL wÄąâ€šĂ„â€¦czone gdy dostĂ„â„˘pne. BÄąâ€šĂ„â„˘dny certyfikat serwera nie powoduje odrzucenia poÄąâ€šĂ„â€¦czenia. */
	GG_SSL_REQUIRED		/**< PoÄąâ€šĂ„â€¦czenie SSL wymagane. BÄąâ€šĂ„â„˘dny certyfikat serwera powoduje odrzucenie poÄąâ€šĂ„â€¦czenia. */
} gg_ssl_t;

/**
 * Sesja Gadu-Gadu.
 *
 * Tworzona przez funkcjĂ„â„˘ \c gg_login(), zwalniana przez \c gg_free_session().
 *
 * \ingroup login
 */
struct gg_session {
	gg_common_head(struct gg_session)

	int async;      	/**< Flaga poÄąâ€šĂ„â€¦czenia asynchronicznego */
	int pid;        	/**< Numer procesu rozwiĂ„â€¦zujĂ„â€¦cego nazwĂ„â„˘ serwera */
	int port;       	/**< Port serwera */
	int seq;        	/**< Numer sekwencyjny ostatniej wiadomoÄąâ€şci */
	int last_pong;  	/**< Czas otrzymania ostatniej ramki utrzymaniowej */
	int last_event;		/**< Czas otrzymania ostatniego pakietu */

	struct gg_event *event;	/**< Zdarzenie po wywoÄąâ€šaniu \c callback */

	uint32_t proxy_addr;	/**< Adres serwera poÄąâ€şredniczĂ„â€¦cego */
	uint16_t proxy_port;	/**< Port serwera poÄąâ€şredniczĂ„â€¦cego */

	uint32_t hub_addr;	/**< Adres huba po rozwiĂ„â€¦zaniu nazwy */
	uint32_t server_addr;	/**< Adres serwera otrzymany od huba */

	uint32_t client_addr;	/**< Adres gniazda dla poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich */
	uint16_t client_port;	/**< Port gniazda dla poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich */

	uint32_t external_addr;	/**< Publiczny adres dla poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich */
	uint16_t external_port;	/**< Publiczny port dla poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich */

	uin_t uin;		/**< WÄąâ€šasny numer Gadu-Gadu */
	char *password;		/**< HasÄąâ€šo (zwalniane po uÄąÄ˝yciu) */

	int initial_status;	/**< PoczĂ„â€¦tkowy status */
	int status;		/**< Aktualny status */

	char *recv_buf;		/**< Bufor na odbierane pakiety. WskaÄąĹźnik zawsze maksymalnie wyrÄ‚Ĺ‚wnany, tak jak w wyniku dziaÄąâ€šania \c malloc(). */
	int recv_done;		/**< Liczba wczytanych bajtÄ‚Ĺ‚w pakietu */
	int recv_left;		/**< Liczba pozostaÄąâ€šych do wczytania bajtÄ‚Ĺ‚w pakietu */

	int protocol_version;	/**< Wersja protokoÄąâ€šu (bez flag) */
	char *client_version;	/**< Wersja klienta */
	int last_sysmsg;	/**< Numer ostatniej wiadomoÄąâ€şci systemowej */

	char *initial_descr;	/**< PoczĂ„â€¦tkowy opis statusu */

	void *resolver;		/**< Dane prywatne procesu lub wĂ„â€¦tku rozwiĂ„â€¦zujĂ„â€¦cego nazwĂ„â„˘ serwera */

#ifndef DOXYGEN
	char *header_buf;	/**< Bufor na poczĂ„â€¦tek nagÄąâ€šÄ‚Ĺ‚wka pakietu (nieaktualne) */
	unsigned int header_done;	/**< Liczba wczytanych bajtÄ‚Ĺ‚w nagÄąâ€šÄ‚Ĺ‚wka pakietu (nieaktualne) */
#endif

#ifdef GG_CONFIG_HAVE_OPENSSL
	SSL *ssl;		/**< Struktura TLS */
	SSL_CTX *ssl_ctx;	/**< Kontekst sesji TLS */
#else
	void *ssl;		/**< Struktura TLS */
	void *ssl_ctx;		/**< Kontekst sesji TLS */
#endif

	int image_size;		/**< Maksymalny rozmiar obsÄąâ€šugiwanych obrazkÄ‚Ĺ‚w w KiB */

	char *userlist_reply;	/**< Bufor z odbieranĂ„â€¦ listĂ„â€¦ kontaktÄ‚Ĺ‚w */

	int userlist_blocks;	/**< Liczba czĂ„â„˘Äąâ€şci listy kontaktÄ‚Ĺ‚w */

	struct gg_image_queue *images;	/**< Lista wczytywanych obrazkÄ‚Ĺ‚w */

	int hash_type;		/**< Rodzaj funkcji skrÄ‚Ĺ‚tu hasÄąâ€ša (\c GG_LOGIN_HASH_GG32 lub \c GG_LOGIN_HASH_SHA1) */

	char *send_buf;		/**< Bufor z danymi do wysÄąâ€šania */
	int send_left;		/**< Liczba bajtÄ‚Ĺ‚w do wysÄąâ€šania */

	struct gg_dcc7 *dcc7_list;	/**< Lista poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich skojarzonych z sesjĂ„â€¦ */
	
	int soft_timeout;	/**< Flaga mÄ‚Ĺ‚wiĂ„â€¦ca, ÄąÄ˝e po przekroczeniu \c timeout naleÄąÄ˝y wywoÄąâ€šaĂ„â€ˇ \c gg_watch_fd() */

	int protocol_flags;	/**< Flagi protokoÄąâ€šu */

	gg_encoding_t encoding;		/**< Rodzaj kodowania znakÄ‚Ĺ‚w */

	gg_resolver_t resolver_type;	/**< SposÄ‚Ĺ‚b rozwiĂ„â€¦zywania nazw serwerÄ‚Ĺ‚w */
	int (*resolver_start)(int *fd, void **private_data, const char *hostname);	/**< Funkcja rozpoczynajĂ„â€¦ca rozwiĂ„â€¦zywanie nazwy */
	void (*resolver_cleanup)(void **private_data, int force);	/**< Funkcja zwalniajĂ„â€¦ca zasoby po rozwiĂ„â€¦zaniu nazwy */

	int protocol_features;	/**< Opcje protokoÄąâ€šu */
	int status_flags;	/**< Flagi statusu */
	int recv_msg_count;	/**< Liczba odebranych wiadomoÄąâ€şci */

	const char *resolver_host;		/**< Nazwa do rozwiĂ„â€¦zania */
	struct in_addr *resolver_result;	/**< Wynik rozwiĂ„â€¦zywania nazwy */
	unsigned int resolver_index;		/**< Indeks aktualnie obsÄąâ€šugiwanego wyniku rozwiĂ„â€¦zywania nazwy */
	unsigned int resolver_count;		/**< Liczba wynikÄ‚Ĺ‚w rozwiĂ„â€¦zywania nazwy */

	uint16_t connect_port[2];		/**< Lista portÄ‚Ĺ‚w do poÄąâ€šĂ„â€¦czenia */
	unsigned int connect_index;		/**< Indeks aktualnie obsÄąâ€šugiwanego portu */

	char *connect_host;			/**< Adres serwera Gadu-Gadu, z ktÄ‚Ĺ‚rym siĂ„â„˘ Äąâ€šĂ„â€¦czymy */
	gg_ssl_t ssl_flag;			/**< Flaga poÄąâ€šĂ„â€¦czenia szyfrowanego */

	struct gg_session_private *private_data;	/**< Prywatne dane sesji, nie udostĂ„â„˘pnione w API */
};

/**
 * PoÄąâ€šĂ„â€¦czenie HTTP.
 *
 * Tworzone przez \c gg_http_connect(), zwalniane przez \c gg_http_free().
 *
 * \ingroup http
 */
struct gg_http {
	gg_common_head(struct gg_http)

	int async;              /**< Flaga poÄąâ€šĂ„â€¦czenia asynchronicznego */
	int pid;                /**< Identyfikator procesu rozwiĂ„â€¦zujĂ„â€¦cego nazwĂ„â„˘ serwera */
	int port;               /**< Port */

	char *query;            /**< Zapytanie HTTP */
	char *header;           /**< Odebrany nagÄąâ€šÄ‚Ĺ‚wek */
	int header_size;        /**< Rozmiar wczytanego nagÄąâ€šÄ‚Ĺ‚wka */
	char *body;             /**< Odebrana strona */
	unsigned int body_size; /**< Rozmiar strony */

	void *data;             /**< Dane prywatne usÄąâ€šugi HTTP */

	char *user_data;	/**< Dane prywatne uÄąÄ˝ytkownika (nie sĂ„â€¦ zwalniane) */

	void *resolver;		/**< Dane prywatne procesu lub wĂ„â€¦tku rozwiĂ„â€¦zujĂ„â€¦cego nazwĂ„â„˘ */

	unsigned int body_done;	/**< Liczba odebranych bajtÄ‚Ĺ‚w strony */

	gg_resolver_t resolver_type;	/**< SposÄ‚Ĺ‚b rozwiĂ„â€¦zywania nazw serwerÄ‚Ĺ‚w */
	int (*resolver_start)(int *fd, void **private_data, const char *hostname);	/**< Funkcja rozpoczynajĂ„â€¦ca rozwiĂ„â€¦zywanie nazwy */
	void (*resolver_cleanup)(void **private_data, int force);	/**< Funkcja zwalniajĂ„â€¦ca zasoby po rozwiĂ„â€¦zaniu nazwy */
};

/** \cond ignore */

#ifdef __GNUC__
#define GG_PACKED __attribute__ ((packed))
#ifndef GG_IGNORE_DEPRECATED
#define GG_DEPRECATED __attribute__ ((deprecated))
#else
#define GG_DEPRECATED
#endif
#else
#define GG_PACKED
#define GG_DEPRECATED
#endif

/** \endcond */

#define GG_MAX_PATH 276		/**< Maksymalny rozmiar nazwy pliku w strukturze \c gg_file_info */

/**
 * Odpowiednik struktury WIN32_FIND_DATA z API WIN32.
 *
 * Wykorzystywana przy poÄąâ€šĂ„â€¦czeniach bezpoÄąâ€şrednich do wersji Gadu-Gadu 6.x.
 */
struct gg_file_info {
	uint32_t mode;			/**< dwFileAttributes */
	uint32_t ctime[2];		/**< ftCreationTime */
	uint32_t atime[2];		/**< ftLastAccessTime */
	uint32_t mtime[2];		/**< ftLastWriteTime */
	uint32_t size_hi;		/**< nFileSizeHigh */
	uint32_t size;			/**< nFileSizeLow */
	uint32_t reserved0;		/**< dwReserved0 */
	uint32_t reserved1;		/**< dwReserved1 */
	unsigned char filename[GG_MAX_PATH - 14];	/**< cFileName */
	unsigned char short_filename[14];		/**< cAlternateFileName */
} /** \cond ignore */ GG_PACKED /** \endcond */;

/**
 * PoÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie do wersji Gadu-Gadu 6.x.
 *
 * Tworzone przez \c gg_dcc_socket_create(), \c gg_dcc_get_file(),
 * \c gg_dcc_send_file() lub \c gg_dcc_voice_chat(), zwalniane przez
 * \c gg_dcc_free().
 *
 * \ingroup dcc6
 */
struct gg_dcc {
	gg_common_head(struct gg_dcc)

	struct gg_event *event;	/**< Zdarzenie po wywoÄąâ€šaniu \c callback */

	int active;		/**< Flaga poÄąâ€šĂ„â€¦czenia aktywnego (nieuÄąÄ˝ywana) */
	int port;		/**< Port gniazda nasÄąâ€šuchujĂ„â€¦cego */
	uin_t uin;		/**< WÄąâ€šasny numer Gadu-Gadu */
	uin_t peer_uin;		/**< Numer Gadu-Gadu drugiej strony poÄąâ€šĂ„â€¦czenia */
	int file_fd;		/**< deskryptor pliku */
	unsigned int offset;	/**< PoÄąâ€šoÄąÄ˝enie w pliku */
	unsigned int chunk_size;
				/**< Rozmiar kawaÄąâ€ška pliku */
	unsigned int chunk_offset;
				/**< PoÄąâ€šoÄąÄ˝enie w aktualnym kawaÄąâ€šku pliku */
	struct gg_file_info file_info;
				/**< Informacje o pliku */
	int established;	/**< Flaga ustanowienia poÄąâ€šĂ„â€¦czenia */
	char *voice_buf;	/**< Bufor na pakiet poÄąâ€šĂ„â€¦czenia gÄąâ€šosowego */
	int incoming;		/**< Flaga poÄąâ€šĂ„â€¦czenia przychodzĂ„â€¦cego */
	char *chunk_buf;	/**< Bufor na fragment danych */
	uint32_t remote_addr;	/**< Adres drugiej strony */
	uint16_t remote_port;	/**< Port drugiej strony */
};

#define GG_DCC7_HASH_LEN	20	/**< Maksymalny rozmiar skrÄ‚Ĺ‚tu pliku w poÄąâ€šĂ„â€¦czeniach bezpoÄąâ€şrenich */
#define GG_DCC7_FILENAME_LEN	255	/**< Maksymalny rozmiar nazwy pliku w poÄąâ€šĂ„â€¦czeniach bezpoÄąâ€şrednich */
#define GG_DCC7_INFO_LEN	32	/**< Maksymalny rozmiar informacji o poÄąâ€šĂ„â€¦czeniach bezpoÄąâ€şrednich */
#define GG_DCC7_INFO_HASH_LEN	32	/**< Maksymalny rozmiar skrÄ‚Ĺ‚tu ip informacji o poÄąâ€šĂ„â€¦czeniach bezpoÄąâ€şrednich */

/**
 * PoÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie od wersji Gadu-Gadu 7.x.
 *
 * \ingroup dcc7
 */
struct gg_dcc7 {
	gg_common_head(struct gg_dcc7)

	gg_dcc7_id_t cid;	/**< Identyfikator poÄąâ€šĂ„â€¦czenia */

	struct gg_event *event;	/**< Struktura zdarzenia */

	uin_t uin;		/**< WÄąâ€šasny numer Gadu-Gadu */
	uin_t peer_uin;		/**< Numer Gadu-Gadu drugiej strony poÄąâ€šĂ„â€¦czenia */

	int file_fd;		/**< Deskryptor przesyÄąâ€šanego pliku */
	unsigned int offset;	/**< Aktualne poÄąâ€šoÄąÄ˝enie w przesyÄąâ€šanym pliku */
	unsigned int size;	/**< Rozmiar przesyÄąâ€šanego pliku */
	unsigned char filename[GG_DCC7_FILENAME_LEN + 1];
				/**< Nazwa przesyÄąâ€šanego pliku */
	unsigned char hash[GG_DCC7_HASH_LEN];
				/**< SkrÄ‚Ĺ‚t SHA1 przesyÄąâ€šanego pliku */

	int dcc_type;		/**< Rodzaj poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego */
	int established;	/**< Flaga ustanowienia poÄąâ€šĂ„â€¦czenia */
	int incoming;		/**< Flaga poÄąâ€šĂ„â€¦czenia przychodzĂ„â€¦cego */
	int reverse;		/**< Flaga poÄąâ€šĂ„â€¦czenia zwrotnego */

	uint32_t local_addr;	/**< Adres lokalny */
	uint16_t local_port;	/**< Port lokalny */

	uint32_t remote_addr;	/**< Adres drugiej strony */
	uint16_t remote_port;	/**< Port drugiej strony */

	struct gg_session *sess;
				/**< Sesja do ktÄ‚Ĺ‚rej przypisano poÄąâ€šĂ„â€¦czenie */
	struct gg_dcc7 *next;	/**< NastĂ„â„˘pne poÄąâ€šĂ„â€¦czenie w liÄąâ€şcie */

	int soft_timeout;	/**< Flaga mÄ‚Ĺ‚wiĂ„â€¦ca, ÄąÄ˝e po przekroczeniu \c timeout naleÄąÄ˝y wywoÄąâ€šaĂ„â€ˇ \c gg_dcc7_watch_fd() */
	int seek;		/**< Flaga mÄ‚Ĺ‚wiĂ„â€¦ca, ÄąÄ˝e moÄąÄ˝na zmieniaĂ„â€ˇ poÄąâ€šoÄąÄ˝enie w wysyÄąâ€šanym pliku */

	void *resolver;		/**< Dane prywatne procesu lub wĂ„â€¦tku rozwiĂ„â€¦zujĂ„â€¦cego nazwĂ„â„˘ serwera */

	int relay;		/**< Flaga mÄ‚Ĺ‚wiĂ„â€¦ca, ÄąÄ˝e laczymy sie przez serwer */
	int relay_index;	/**< Numer serwera poÄąâ€şredniczĂ„â€¦cego, do ktÄ‚Ĺ‚rego siĂ„â„˘ Äąâ€šĂ„â€¦czymy */
	int relay_count;	/**< Rozmiar listy serwerÄ‚Ĺ‚w poÄąâ€şredniczĂ„â€¦cych */
	struct gg_dcc7_relay *relay_list;	/**< Lista serwerÄ‚Ĺ‚w poÄąâ€şredniczĂ„â€¦cych */
};

/**
 * Rodzaj sesji.
 */
enum gg_session_t {
	GG_SESSION_GG = 1,	/**< PoÄąâ€šĂ„â€¦czenie z serwerem Gadu-Gadu */
	GG_SESSION_HTTP,	/**< PoÄąâ€šĂ„â€¦czenie HTTP */
	GG_SESSION_SEARCH,	/**< Wyszukiwanie w katalogu publicznym (nieaktualne) */
	GG_SESSION_REGISTER,	/**< Rejestracja nowego konta */
	GG_SESSION_REMIND,	/**< Przypominanie hasÄąâ€ša */
	GG_SESSION_PASSWD,	/**< Zmiana hasÄąâ€ša */
	GG_SESSION_CHANGE,	/**< Zmiana informacji w katalogu publicznym (nieaktualne) */
	GG_SESSION_DCC,		/**< PoÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (do wersji 6.x) */
	GG_SESSION_DCC_SOCKET,	/**< Gniazdo nasÄąâ€šuchujĂ„â€¦ce (do wersji 6.x) */
	GG_SESSION_DCC_SEND,	/**< WysyÄąâ€šanie pliku (do wersji 6.x) */
	GG_SESSION_DCC_GET,	/**< Odbieranie pliku (do wersji 6.x) */
	GG_SESSION_DCC_VOICE,	/**< Rozmowa gÄąâ€šosowa (do wersji 6.x) */
	GG_SESSION_USERLIST_GET,	/**< Import listy kontaktÄ‚Ĺ‚w z serwera (nieaktualne) */
	GG_SESSION_USERLIST_PUT,	/**< Eksport listy kontaktÄ‚Ĺ‚w do serwera (nieaktualne) */
	GG_SESSION_UNREGISTER,	/**< Usuwanie konta */
	GG_SESSION_USERLIST_REMOVE,	/**< Usuwanie listy kontaktÄ‚Ĺ‚w z serwera (nieaktualne) */
	GG_SESSION_TOKEN,	/**< Pobieranie tokenu */
	GG_SESSION_DCC7_SOCKET,	/**< Gniazdo nasÄąâ€šuchujĂ„â€¦ce (od wersji 7.x) */
	GG_SESSION_DCC7_SEND,	/**< WysyÄąâ€šanie pliku (od wersji 7.x) */
	GG_SESSION_DCC7_GET,	/**< Odbieranie pliku (od wersji 7.x) */
	GG_SESSION_DCC7_VOICE,	/**< Rozmowa gÄąâ€šosowa (od wersji 7.x) */

	GG_SESSION_USER0 = 256,	/**< Rodzaj zadeklarowany dla uÄąÄ˝ytkownika */
	GG_SESSION_USER1,	/**< Rodzaj zadeklarowany dla uÄąÄ˝ytkownika */
	GG_SESSION_USER2,	/**< Rodzaj zadeklarowany dla uÄąÄ˝ytkownika */
	GG_SESSION_USER3,	/**< Rodzaj zadeklarowany dla uÄąÄ˝ytkownika */
	GG_SESSION_USER4,	/**< Rodzaj zadeklarowany dla uÄąÄ˝ytkownika */
	GG_SESSION_USER5,	/**< Rodzaj zadeklarowany dla uÄąÄ˝ytkownika */
	GG_SESSION_USER6,	/**< Rodzaj zadeklarowany dla uÄąÄ˝ytkownika */
	GG_SESSION_USER7	/**< Rodzaj zadeklarowany dla uÄąÄ˝ytkownika */
};

/**
 * Aktualny stan sesji.
 */
enum gg_state_t {
	/* wspÄ‚Ĺ‚lne */
	GG_STATE_IDLE = 0,		/**< Nie dzieje siĂ„â„˘ nic */
	GG_STATE_RESOLVING,             /**< Oczekiwanie na rozwiĂ„â€¦zanie nazwy serwera */
	GG_STATE_CONNECTING,            /**< Oczekiwanie na poÄąâ€šĂ„â€¦czenie */
	GG_STATE_READING_DATA,		/**< Oczekiwanie na dane */
	GG_STATE_ERROR,			/**< Kod bÄąâ€šĂ„â„˘du w polu \c error */

	/* gg_session */
	GG_STATE_CONNECTING_HUB,	/**< Oczekiwanie na poÄąâ€šĂ„â€¦czenie z hubem */
	GG_STATE_CONNECTING_GG,         /**< Oczekiwanie na poÄąâ€šĂ„â€¦czenie z serwerem */
	GG_STATE_READING_KEY,           /**< Oczekiwanie na klucz */
	GG_STATE_READING_REPLY,         /**< Oczekiwanie na odpowiedÄąĹź serwera */
	GG_STATE_CONNECTED,             /**< PoÄąâ€šĂ„â€¦czono z serwerem */

	/* gg_http */
	GG_STATE_SENDING_QUERY,		/**< WysÄąâ€šano zapytanie HTTP */
	GG_STATE_READING_HEADER,	/**< Oczekiwanie na nagÄąâ€šÄ‚Ĺ‚wek HTTP */
	GG_STATE_PARSING,               /**< Przetwarzanie danych */
	GG_STATE_DONE,                  /**< PoÄąâ€šĂ„â€¦czenie zakoÄąâ€žczone */

	/* gg_dcc */
	GG_STATE_LISTENING,		/* czeka na poÄąâ€šĂ„â€¦czenia */
	GG_STATE_READING_UIN_1,		/* czeka na uin peera */
	GG_STATE_READING_UIN_2,		/* czeka na swÄ‚Ĺ‚j uin */
	GG_STATE_SENDING_ACK,		/* wysyÄąâ€ša potwierdzenie dcc */
	GG_STATE_READING_ACK,		/* czeka na potwierdzenie dcc */
	GG_STATE_READING_REQUEST,	/* czeka na komendĂ„â„˘ */
	GG_STATE_SENDING_REQUEST,	/* wysyÄąâ€ša komendĂ„â„˘ */
	GG_STATE_SENDING_FILE_INFO,	/* wysyÄąâ€ša informacje o pliku */
	GG_STATE_READING_PRE_FILE_INFO,	/* czeka na pakiet przed file_info */
	GG_STATE_READING_FILE_INFO,	/* czeka na informacje o pliku */
	GG_STATE_SENDING_FILE_ACK,	/* wysyÄąâ€ša potwierdzenie pliku */
	GG_STATE_READING_FILE_ACK,	/* czeka na potwierdzenie pliku */
	GG_STATE_SENDING_FILE_HEADER,	/* wysyÄąâ€ša nagÄąâ€šÄ‚Ĺ‚wek pliku */
	GG_STATE_READING_FILE_HEADER,	/* czeka na nagÄąâ€šÄ‚Ĺ‚wek */
	GG_STATE_GETTING_FILE,		/* odbiera plik */
	GG_STATE_SENDING_FILE,		/* wysyÄąâ€ša plik */
	GG_STATE_READING_VOICE_ACK,	/* czeka na potwierdzenie voip */
	GG_STATE_READING_VOICE_HEADER,	/* czeka na rodzaj bloku voip */
	GG_STATE_READING_VOICE_SIZE,	/* czeka na rozmiar bloku voip */
	GG_STATE_READING_VOICE_DATA,	/* czeka na dane voip */
	GG_STATE_SENDING_VOICE_ACK,	/* wysyÄąâ€ša potwierdzenie voip */
	GG_STATE_SENDING_VOICE_REQUEST,	/* wysyÄąâ€ša ÄąÄ˝Ă„â€¦danie voip */
	GG_STATE_READING_TYPE,		/* czeka na typ poÄąâ€šĂ„â€¦czenia */

	/* nowe. bez sensu jest to API. */
	GG_STATE_TLS_NEGOTIATION,	/**< Negocjacja poÄąâ€šĂ„â€¦czenia szyfrowanego */

	GG_STATE_REQUESTING_ID,		/**< Oczekiwanie na nadanie identyfikatora poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego */
	GG_STATE_WAITING_FOR_ACCEPT,	/**< Oczekiwanie na potwierdzenie lub odrzucenie poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego */
	GG_STATE_WAITING_FOR_INFO,	/**< Oczekiwanie na informacje o poÄąâ€šĂ„â€¦czeniu bezpoÄąâ€şrednim */

	GG_STATE_READING_ID,		/**< Odebranie identyfikatora poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego */
	GG_STATE_SENDING_ID,		/**< WysÄąâ€šano identyfikator poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego */
	GG_STATE_RESOLVING_GG,		/**< Oczekiwanie na rozwiĂ„â€¦zanie nazwy serwera Gadu-Gadu */

	GG_STATE_RESOLVING_RELAY,	/**< Oczekiwanie na rozwiĂ„â€¦zanie nazwy serwera poÄąâ€şredniczĂ„â€¦cego */
	GG_STATE_CONNECTING_RELAY,	/**< Oczekiwanie na poÄąâ€šĂ„â€¦czenie z serwerem poÄąâ€şredniczĂ„â€¦cym */
	GG_STATE_READING_RELAY,		/**< Odbieranie danych */

	GG_STATE_DISCONNECTING,		/**< Oczekiwanie na potwierdzenie rozÄąâ€šĂ„â€¦czenia */

	GG_STATE_CONNECT_HUB,		/**< NawiĂ„â€¦zanie poÄąâ€šĂ„â€¦czenia z hubem */
	GG_STATE_CONNECT_PROXY_HUB,
	GG_STATE_CONNECT_GG,		/**< NawiĂ„â€¦zanie poÄąâ€šĂ„â€¦czenia z serwerem */
	GG_STATE_CONNECT_PROXY_GG,
	GG_STATE_CONNECTING_PROXY_HUB,
	GG_STATE_CONNECTING_PROXY_GG,
	GG_STATE_RESOLVE_HUB_SYNC,
	GG_STATE_RESOLVE_HUB_ASYNC,
	GG_STATE_RESOLVE_PROXY_HUB_SYNC,
	GG_STATE_RESOLVE_PROXY_HUB_ASYNC,
	GG_STATE_RESOLVE_PROXY_GG_SYNC,
	GG_STATE_RESOLVE_PROXY_GG_ASYNC,
	GG_STATE_RESOLVE_GG_SYNC,
	GG_STATE_RESOLVE_GG_ASYNC,
	GG_STATE_RESOLVING_HUB,
	GG_STATE_RESOLVING_PROXY_HUB,
	GG_STATE_RESOLVING_PROXY_GG,
	GG_STATE_SEND_HUB,
	GG_STATE_SEND_PROXY_HUB,
	GG_STATE_SEND_PROXY_GG,
	GG_STATE_SENDING_HUB,
	GG_STATE_SENDING_PROXY_HUB,
	GG_STATE_SENDING_PROXY_GG,
	GG_STATE_READING_HUB,
	GG_STATE_READING_PROXY_HUB,
	GG_STATE_READING_PROXY_GG,
};

/**
 * Informacja o tym, czy biblioteka chce zapisywaĂ„â€ˇ i/lub czytaĂ„â€ˇ
 * z deskryptora. Maska bitowa.
 *
 * \ingroup events
 */
enum gg_check_t {
	GG_CHECK_NONE = 0,		/**< Nie sprawdzaj niczego */
	GG_CHECK_WRITE = 1,		/**< SprawdÄąĹź moÄąÄ˝liwoÄąâ€şĂ„â€ˇ zapisu */
	GG_CHECK_READ = 2		/**< SprawdÄąĹź moÄąÄ˝liwoÄąâ€şĂ„â€ˇ odczytu */
};

/**
 * Metody nawiĂ„â€¦zywania poÄąâ€šĂ„â€¦czeÄąâ€ž TCP/TLS.
 *
 * \ingroup socketmanager
 */
typedef enum {
	GG_SOCKET_MANAGER_TYPE_INTERNAL = 0, /**< WewnĂ„â„˘trzna obsÄąâ€šuga gniazd (domyÄąâ€şlne). */
	GG_SOCKET_MANAGER_TYPE_TCP, /**< Dostarczona przez aplikacjĂ„â„˘ - tylko obsÄąâ€šuga TCP. */
	GG_SOCKET_MANAGER_TYPE_TLS /**< Dostarczona przez aplikacjĂ„â„˘ - obsÄąâ€šuga zarÄ‚Ĺ‚wno TCP, jak i TLS. */
} gg_socket_manager_type_t;

/**
 * Funkcja dostarczona przez aplikacjĂ„â„˘, tworzĂ„â€¦ca nowe gniazdo TCP/TLS.
 *
 * Po nawiĂ„â€¦zaniu poÄąâ€šĂ„â€¦czenia aplikacja musi wywoÄąâ€šaĂ„â€ˇ gg_socket_manager_connected.
 * JeÄąÄ˝eli poÄąâ€šĂ„â€¦czenie jest asynchroniczne, wywoÄąâ€šanie musi nastĂ„â€¦piĂ„â€ˇ po wyjÄąâ€şciu z
 * kontekstu tej funkcji. Dla poÄąâ€šĂ„â€¦czeÄąâ€ž synchronicznych z kolei, musi nastĂ„â€¦piĂ„â€ˇ
 * jeszcze przed wyjÄąâ€şciem z kontekstu.
 *
 * \param cb_data Dane prywatne aplikacji
 * \param host Nazwa hosta
 * \param port Numer portu
 * \param is_tls Flaga okreÄąâ€şlajĂ„â€¦ca, czy ma zostaĂ„â€ˇ nawiĂ„â€¦zane poÄąâ€šĂ„â€¦czenie TLS
 * \param is_async Flaga okreÄąâ€şlajĂ„â€¦ca poÄąâ€šĂ„â€¦czenie asynchroniczne (patrz szczegÄ‚Ĺ‚Äąâ€šy powyÄąÄ˝ej)
 * \param priv Dane prywatne biblioteki libgadu (do przekazania do gg_socket_manager_connected)
 *
 * \return Uchwyt gniazda
 *
 * \ingroup socketmanager
 */
typedef void* (*gg_socket_manager_connect_cb_t)(void *cb_data, const char *host, int port, int is_tls, int is_async, void *priv);

/**
 * Niszczy gniazdo i zwalnia wszystkie powiĂ„â€¦zane z nim zasoby.
 *
 * \param cb_data Dane prywatne aplikacji
 * \param handle Uchwyt gniazda
 *
 * \ingroup socketmanager
 */
typedef void (*gg_socket_manager_close_cb_t)(void *cb_data, void *handle);

/**
 * Odbiera z gniazda dane binarne.
 *
 * Funkcja powinna zajmowaĂ„â€ˇ siĂ„â„˘ obsÄąâ€šugĂ„â€¦ TLS, jeÄąÄ˝eli gniazdo jest w takim trybie.
 *
 * \param cb_data Dane prywatne aplikacji
 * \param handle Uchwyt gniazda
 * \param buffer Bufor do zapisu danych
 * \param bufsize Rozmiar bufora
 *
 * \return IloÄąâ€şĂ„â€ˇ zapisanych danych, lub -1 (oraz ustawiony errno) w przypadku niepowodzenia
 *
 * \ingroup socketmanager
 */
typedef ssize_t (*gg_socket_manager_read_cb_t)(void *cb_data, void *handle, unsigned char *buffer, size_t bufsize);

/**
 * WysyÄąâ€ša przez gniazdo dane binarne.
 *
 * Funkcja powinna zajmowaĂ„â€ˇ siĂ„â„˘ obsÄąâ€šugĂ„â€¦ TLS, jeÄąÄ˝eli gniazdo jest w takim trybie.
 *
 * \param cb_data Dane prywatne aplikacji
 * \param handle Uchwyt gniazda
 * \param data Dane do wysÄąâ€šania
 * \param length Rozmiar danych
 *
 * \return IloÄąâ€şĂ„â€ˇ wysÄąâ€šanych danych, lub -1 (oraz ustawiony errno) w przypadku niepowodzenia
 *
 * \ingroup socketmanager
 */
typedef ssize_t (*gg_socket_manager_write_cb_t)(void *cb_data, void *handle, const unsigned char *data, size_t length);

/**
 * Struktura opisujĂ„â€¦ca funkcje zarzĂ„â€¦dzajĂ„â€¦ce gniazdami, jeÄąÄ˝eli aplikacja sama je
 * obsÄąâ€šuguje.
 *
 * \ingroup socketmanager
 */
typedef struct {
	void *cb_data; /**< Dane prywatne aplikacji */
	gg_socket_manager_connect_cb_t connect_cb; /**< Funkcja tworzĂ„â€¦ca nowe gniazdo */
	gg_socket_manager_close_cb_t close_cb; /**< Funkcja niszczĂ„â€¦ca gniazdo */
	gg_socket_manager_read_cb_t read_cb; /**< Funkcja odczytujĂ„â€¦ca dane z gniazda */
	gg_socket_manager_write_cb_t write_cb; /**< Funkcja wysyÄąâ€šajĂ„â€¦ca dane przez gniazdo */
#ifndef DOXYGEN
	void *reserved1;
	void *reserved2;
	void *reserved3;
	void *reserved4;
#endif
} gg_socket_manager_t;

int gg_socket_manager_connected(void *handle, void *priv, int fd);

/**
 * Parametry poÄąâ€šĂ„â€¦czenia z serwerem Gadu-Gadu. Parametry zostaÄąâ€šy przeniesione
 * do struktury, by uniknĂ„â€¦Ă„â€ˇ zmian API po rozszerzeniu protokoÄąâ€šu i dodaniu
 * kolejnych opcji poÄąâ€šĂ„â€¦czenia. CzĂ„â„˘Äąâ€şĂ„â€ˇ parametrÄ‚Ĺ‚w, ktÄ‚Ĺ‚re nie sĂ„â€¦ juÄąÄ˝ aktualne
 * lub nie majĂ„â€¦ znaczenia, zostaÄąâ€ša usuniĂ„â„˘ta z dokumentacji.
 *
 * \ingroup login
 */
struct gg_login_params {
	uin_t uin;			/**< Numer Gadu-Gadu */
	char *password;			/**< HasÄąâ€šo */
	int async;			/**< Flaga asynchronicznego poÄąâ€šĂ„â€¦czenia (domyÄąâ€şlnie nie) */
	int status;			/**< PoczĂ„â€¦tkowy status uÄąÄ˝ytkownika (domyÄąâ€şlnie \c GG_STATUS_AVAIL) */
	char *status_descr;		/**< PoczĂ„â€¦tkowy opis uÄąÄ˝ytkownika (domyÄąâ€şlnie brak) */
	uint32_t server_addr;		/**< Adres serwera Gadu-Gadu (domyÄąâ€şlnie pobierany automatycznie) */
	uint16_t server_port;		/**< Port serwera Gadu-Gadu (domyÄąâ€şlnie pobierany automatycznie) */
	uint32_t client_addr;		/**< Adres poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich (domyÄąâ€şlnie dobierany automatycznie) */
	uint16_t client_port;		/**< Port poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich (domyÄąâ€şlnie dobierany automatycznie) */
	int protocol_version;		/**< Wersja protokoÄąâ€šu wysyÄąâ€šana do serwera (domyÄąâ€şlnie najnowsza obsÄąâ€šugiwana) */
	char *client_version;		/**< Wersja klienta wysyÄąâ€šana do serwera (domyÄąâ€şlnie najnowsza znana) */
	int has_audio;			/**< Flaga obsÄąâ€šugi poÄąâ€šĂ„â€¦czeÄąâ€ž gÄąâ€šosowych */
	int last_sysmsg;		/**< Numer ostatnio odebranej wiadomoÄąâ€şci systemowej */
	uint32_t external_addr;		/**< Adres publiczny dla poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich (domyÄąâ€şlnie dobierany automatycznie) */
	uint16_t external_port;		/**< Port publiczny dla poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich (domyÄąâ€şlnie dobierany automatycznie) */
	int tls;			/**< Flaga poÄąâ€šĂ„â€¦czenia szyfrowanego (patrz \ref gg_ssl_t) */
	int image_size;			/**< Maksymalny rozmiar obsÄąâ€šugiwanych obrazkÄ‚Ĺ‚w w kilobajtach */
#ifndef DOXYGEN
	int era_omnix;			/**< Flaga udawania klienta Era Omnix (nieaktualna) */
#endif
	int hash_type;			/**< Rodzaj skrÄ‚Ĺ‚tu hasÄąâ€ša (\c GG_LOGIN_HASH_GG32 lub \c GG_LOGIN_HASH_SHA1, domyÄąâ€şlnie SHA1) */
	gg_encoding_t encoding;		/**< Rodzaj kodowania uÄąÄ˝ywanego w sesji (domyÄąâ€şlnie CP1250) */
	gg_resolver_t resolver;		/**< SposÄ‚Ĺ‚b rozwiĂ„â€¦zywania nazw (patrz \ref build-resolver) */
	int protocol_features;		/**< Opcje protokoÄąâ€šu (flagi GG_FEATURE_*). */
	int status_flags;		/**< Flagi statusu (flagi GG_STATUS_FLAG_*, patrz \ref status). */

	unsigned int struct_size;	/**< Rozmiar struktury. To pole powinno byĂ„â€ˇ inicjowane wartoÄąâ€şciĂ„â€¦ sizeof(struct gg_login_params) - w przeciwnym przypadku pola za nim nie bĂ„â„˘dĂ„â€¦ obsÄąâ€šugiwane. Pozwala na rozszerzanie struktury bez Äąâ€šamania ABI. */

	gg_compat_t compatibility;	/**< StopieÄąâ€ž kompatybilnoÄąâ€şci ze starym API. */

	char *connect_host;		/**< Nazwa hosta (oraz opcjonalnie port, podany po dwukropku) serwera Gadu-Gadu (domyÄąâ€şlnie pobierany automatycznie) (patrz pole struct_size). */

	gg_socket_manager_type_t socket_manager_type; /**< Wybrana metoda nawiĂ„â€¦zywania poÄąâ€šĂ„â€¦czeÄąâ€ž TCP/TLS (domyÄąâ€şlnie wewnĂ„â„˘trzna) */
	gg_socket_manager_t socket_manager; /**< JeÄąÄ˝eli wybrano metodĂ„â„˘ zewnĂ„â„˘trznĂ„â€¦ - konfiguracja jej */

	char **host_white_list;		/**< Lista zakoÄąâ€žczona wskaÄąĹźnikiem NULL, domen akceptowanych w odpowiedziach od huba (domyÄąâ€şlnie wszystkie do tej pory znane). UÄąÄ˝ywane tylko przy GG_SSL_REQUIRED. Pusta lista wyÄąâ€šĂ„â€¦cza sprawdzanie. */
};

#ifdef GG_CONFIG_IS_GPL_COMPLIANT
int gg_is_gpl_compliant(void);
#endif
struct gg_session *gg_login(const struct gg_login_params *p);
void gg_free_session(struct gg_session *sess);
void gg_logoff(struct gg_session *sess);
int gg_change_status(struct gg_session *sess, int status);
int gg_change_status_descr(struct gg_session *sess, int status, const char *descr);
int gg_change_status_descr_time(struct gg_session *sess, int status, const char *descr, int time);
int gg_change_status_flags(struct gg_session *sess, int flags);
int gg_send_message(struct gg_session *sess, int msgclass, uin_t recipient, const unsigned char *message);
int gg_send_message_richtext(struct gg_session *sess, int msgclass, uin_t recipient, const unsigned char *message, const unsigned char *format, int formatlen);
int gg_send_message_html(struct gg_session *sess, int msgclass, uin_t recipient, const unsigned char *html_message);
int gg_send_message_confer(struct gg_session *sess, int msgclass, int recipients_count, uin_t *recipients, const unsigned char *message);
int gg_send_message_confer_richtext(struct gg_session *sess, int msgclass, int recipients_count, uin_t *recipients, const unsigned char *message, const unsigned char *format, int formatlen);
int gg_send_message_confer_html(struct gg_session *sess, int msgclass, int recipients_count, uin_t *recipients, const unsigned char *html_message);
int gg_send_message_ctcp(struct gg_session *sess, int msgclass, uin_t recipient, const unsigned char *message, int message_len);
int gg_ping(struct gg_session *sess);
int gg_userlist_request(struct gg_session *sess, char type, const char *request);
int gg_userlist100_request(struct gg_session *sess, char type, unsigned int version, char format_type, const char *request);
int gg_image_request(struct gg_session *sess, uin_t recipient, int size, uint32_t crc32);
int gg_image_reply(struct gg_session *sess, uin_t recipient, const char *filename, const char *image, int size);
int gg_typing_notification(struct gg_session *sess, uin_t recipient, int length);

uint32_t gg_crc32(uint32_t crc, const unsigned char *buf, int len);

int gg_session_set_resolver(struct gg_session *gs, gg_resolver_t type);
gg_resolver_t gg_session_get_resolver(struct gg_session *gs);
int gg_session_set_custom_resolver(struct gg_session *gs, int (*resolver_start)(int*, void**, const char*), void (*resolver_cleanup)(void**, int));

int gg_http_set_resolver(struct gg_http *gh, gg_resolver_t type);
gg_resolver_t gg_http_get_resolver(struct gg_http *gh);
int gg_http_set_custom_resolver(struct gg_http *gh, int (*resolver_start)(int*, void**, const char*), void (*resolver_cleanup)(void**, int));

int gg_global_set_resolver(gg_resolver_t type);
gg_resolver_t gg_global_get_resolver(void);
int gg_global_set_custom_resolver(int (*resolver_start)(int*, void**, const char*), void (*resolver_cleanup)(void**, int));

int gg_multilogon_disconnect(struct gg_session *gs, gg_multilogon_id_t conn_id);

int gg_chat_create(struct gg_session *gs);
int gg_chat_invite(struct gg_session *gs, uint64_t id, uin_t *participants, unsigned int participants_count);
int gg_chat_leave(struct gg_session *gs, uint64_t id);
int gg_chat_send_message(struct gg_session *gs, uint64_t id, const char *message, int is_html);

/**
 * Rodzaj zdarzenia.
 *
 * \ingroup events
 */
enum gg_event_t {
	GG_EVENT_NONE = 0,		/**< Nie wydarzyÄąâ€šo siĂ„â„˘ nic wartego uwagi */
	GG_EVENT_MSG,			/**< \brief Otrzymano wiadomoÄąâ€şĂ„â€ˇ. Przekazuje rÄ‚Ĺ‚wnieÄąÄ˝ wiadomoÄąâ€şci systemowe od numeru 0. */
	GG_EVENT_NOTIFY,		/**< \brief Informacja o statusach osÄ‚Ĺ‚b z listy kontaktÄ‚Ĺ‚w (przed 6.0). Zdarzenie naleÄąÄ˝y obsÄąâ€šugiwaĂ„â€ˇ, jeÄąâ€şli planuje siĂ„â„˘ uÄąÄ˝ywaĂ„â€ˇ protokoÄąâ€šu w wersji starszej niÄąÄ˝ domyÄąâ€şlna. Ostatni element tablicy zawiera uin rÄ‚Ĺ‚wny 0, a pozostaÄąâ€še pola sĂ„â€¦ niezainicjowane. */
	GG_EVENT_NOTIFY_DESCR,		/**< \brief Informacja o statusie opisowym osoby z listy kontaktÄ‚Ĺ‚w (przed 6.0). Zdarzenie naleÄąÄ˝y obsÄąâ€šugiwaĂ„â€ˇ, jeÄąâ€şli planuje siĂ„â„˘ uÄąÄ˝ywaĂ„â€ˇ protokoÄąâ€šu w wersji starszej niÄąÄ˝ domyÄąâ€şlna. */
	GG_EVENT_STATUS,		/**< \brief Zmiana statusu osoby z listy kontaktÄ‚Ĺ‚w (przed 6.0). Zdarzenie naleÄąÄ˝y obsÄąâ€šugiwaĂ„â€ˇ, jeÄąâ€şli planuje siĂ„â„˘ uÄąÄ˝ywaĂ„â€ˇ protokoÄąâ€šu w wersji starszej niÄąÄ˝ domyÄąâ€şlna. */
	GG_EVENT_ACK,			/**< Potwierdzenie dorĂ„â„˘czenia wiadomoÄąâ€şci */
	GG_EVENT_PONG,			/**< \brief Utrzymanie poÄąâ€šĂ„â€¦czenia. Obecnie serwer nie wysyÄąâ€ša juÄąÄ˝ do klienta ramek utrzymania poÄąâ€šĂ„â€¦czenia, polega wyÄąâ€šĂ„â€¦cznie na wysyÄąâ€šaniu ramek przez klienta. */
	GG_EVENT_CONN_FAILED,		/**< \brief Nie udaÄąâ€šo siĂ„â„˘ poÄąâ€šĂ„â€¦czyĂ„â€ˇ */
	GG_EVENT_CONN_SUCCESS,		/**< \brief PoÄąâ€šĂ„â€¦czono z serwerem. PierwszĂ„â€¦ rzeczĂ„â€¦, jakĂ„â€¦ naleÄąÄ˝y zrobiĂ„â€ˇ jest wysÄąâ€šanie listy kontaktÄ‚Ĺ‚w. */
	GG_EVENT_DISCONNECT,		/**< \brief Serwer zrywa poÄąâ€šĂ„â€¦czenie. Zdarza siĂ„â„˘, gdy rÄ‚Ĺ‚wnolegle do serwera podÄąâ€šĂ„â€¦czy siĂ„â„˘ druga sesja i trzeba zerwaĂ„â€ˇ poÄąâ€šĂ„â€¦czenie z pierwszĂ„â€¦. */

	GG_EVENT_DCC_NEW,		/**< Nowe poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (6.x) */
	GG_EVENT_DCC_ERROR,		/**< BÄąâ€šĂ„â€¦d poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego (6.x) */
	GG_EVENT_DCC_DONE,		/**< ZakoÄąâ€žczono poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (6.x) */
	GG_EVENT_DCC_CLIENT_ACCEPT,	/**< Moment akceptacji klienta w poÄąâ€šĂ„â€¦czeniu bezpoÄąâ€şrednim (6.x) */
	GG_EVENT_DCC_CALLBACK,		/**< Zwrotne poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (6.x) */
	GG_EVENT_DCC_NEED_FILE_INFO,	/**< NaleÄąÄ˝y wypeÄąâ€šniĂ„â€ˇ \c file_info dla poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego (6.x) */
	GG_EVENT_DCC_NEED_FILE_ACK,	/**< Czeka na potwierdzenie pliku w poÄąâ€šĂ„â€¦czeniu bezpoÄąâ€şrednim (6.x) */
	GG_EVENT_DCC_NEED_VOICE_ACK,	/**< Czeka na potwierdzenie rozmowy w poÄąâ€šĂ„â€¦czeniu bezpoÄąâ€şrednim (6.x) */
	GG_EVENT_DCC_VOICE_DATA, 	/**< Dane bezpoÄąâ€şredniego poÄąâ€šĂ„â€¦czenia gÄąâ€šosowego (6.x) */

	GG_EVENT_PUBDIR50_SEARCH_REPLY,	/**< OdpowiedÄąĹź katalogu publicznego */
	GG_EVENT_PUBDIR50_READ,		/**< Odczytano wÄąâ€šasne dane z katalogu publicznego */
	GG_EVENT_PUBDIR50_WRITE,	/**< Zmieniono wÄąâ€šasne dane w katalogu publicznym */

	GG_EVENT_STATUS60,		/**< Zmiana statusu osoby z listy kontaktÄ‚Ĺ‚w */
	GG_EVENT_NOTIFY60,		/**< Informacja o statusach osÄ‚Ĺ‚b z listy kontaktÄ‚Ĺ‚w. Ostatni element tablicy zawiera uin rÄ‚Ĺ‚wny 0, a pozostaÄąâ€še pola sĂ„â€¦ niezainicjowane.  */
	GG_EVENT_USERLIST,		/**< Wynik importu lub eksportu listy kontaktÄ‚Ĺ‚w */
	GG_EVENT_IMAGE_REQUEST,		/**< ÄąÂ»Ă„â€¦danie przesÄąâ€šania obrazka z wiadomoÄąâ€şci */
	GG_EVENT_IMAGE_REPLY,		/**< PrzysÄąâ€šano obrazek z wiadomoÄąâ€şci */
	GG_EVENT_DCC_ACK,		/**< Potwierdzenie transmisji w poÄąâ€šĂ„â€¦czeniu bezpoÄąâ€şrednim (6.x) */

	GG_EVENT_DCC7_NEW,		/**< Nowe poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (7.x) */
	GG_EVENT_DCC7_ACCEPT,		/**< Zaakceptowano poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (7.x), nowy deskryptor */
	GG_EVENT_DCC7_REJECT,		/**< Odrzucono poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (7.x) */
	GG_EVENT_DCC7_CONNECTED,	/**< Zestawiono poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (7.x), nowy deskryptor */
	GG_EVENT_DCC7_ERROR,		/**< BÄąâ€šĂ„â€¦d poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego (7.x) */
	GG_EVENT_DCC7_DONE,		/**< ZakoÄąâ€žczono poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (7.x) */
	GG_EVENT_DCC7_PENDING,		/**< Trwa prÄ‚Ĺ‚ba poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego (7.x), nowy deskryptor */

	GG_EVENT_XML_EVENT,		/**< Otrzymano komunikat systemowy (7.7) */
	GG_EVENT_DISCONNECT_ACK,	/**< \brief Potwierdzenie zakoÄąâ€žczenia sesji. Informuje o tym, ÄąÄ˝e zmiana stanu na niedostĂ„â„˘pny z opisem dotarÄąâ€ša do serwera i moÄąÄ˝na zakoÄąâ€žczyĂ„â€ˇ poÄąâ€šĂ„â€¦czenie TCP. */
	GG_EVENT_TYPING_NOTIFICATION,	/**< Powiadomienie o pisaniu */
	GG_EVENT_USER_DATA,		/**< Informacja o kontaktach */
	GG_EVENT_MULTILOGON_MSG,	/**< WiadomoÄąâ€şĂ„â€ˇ wysÄąâ€šana z innej sesji multilogowania */
	GG_EVENT_MULTILOGON_INFO,	/**< Informacja o innych sesjach multilogowania */

	GG_EVENT_USERLIST100_VERSION,	/**< Otrzymano numer wersji listy kontaktÄ‚Ĺ‚w na serwerze (10.0) */
	GG_EVENT_USERLIST100_REPLY,	/**< Wynik importu lub eksportu listy kontaktÄ‚Ĺ‚w (10.0) */

	GG_EVENT_IMTOKEN,		/**< Otrzymano ciĂ„â€¦g IMTOKEN (11.0) */
	GG_EVENT_PONG110,		/**< \brief Utrzymanie poÄąâ€šĂ„â€¦czenia (11.0). MoÄąÄ˝e sÄąâ€šuÄąÄ˝yĂ„â€ˇ do synchronizacji czasu z serwerem. */
	GG_EVENT_JSON_EVENT,		/**< Otrzymano komunikat systemowy (11.0) */
	GG_EVENT_ACK110,		/**< Potwierdzenie wysÄąâ€šania wiadomoÄąâ€şci (11.0) */

	GG_EVENT_CHAT_INFO,		/**< Otrzymano informacjĂ„â„˘ o konferencji (11.0). */
	GG_EVENT_CHAT_INFO_GOT_ALL,	/**< \brief Informacje o wszystkich konferencjach zostaÄąâ€šy juÄąÄ˝ wysÄąâ€šane (11.0). Otrzymywany po ostatnim pakiecie \c GG_EVENT_CHAT_INFO */
	GG_EVENT_CHAT_INFO_UPDATE,	/**< \brief Aktualizacja informacji o konferencji (11.0). Dodanie, usuniĂ„â„˘cie jednego z uczestnikÄ‚Ĺ‚w. */
	GG_EVENT_CHAT_CREATED,		/**< Potwierdzenie utworzenia konferencji (11.0) */
	GG_EVENT_CHAT_INVITE_ACK,	/**< Potwierdzenie wysÄąâ€šania zaproszenia do konferencji (11.0) */
};

#define GG_EVENT_SEARCH50_REPLY GG_EVENT_PUBDIR50_SEARCH_REPLY

/**
 * PowÄ‚Ĺ‚d nieudanego poÄąâ€šĂ„â€¦czenia.
 */
enum gg_failure_t {
	GG_FAILURE_RESOLVING = 1,	/**< Nie znaleziono serwera */
	GG_FAILURE_CONNECTING,		/**< BÄąâ€šĂ„â€¦d poÄąâ€šĂ„â€¦czenia */
	GG_FAILURE_INVALID,		/**< Serwer zwrÄ‚Ĺ‚ciÄąâ€š nieprawidÄąâ€šowe dane */
	GG_FAILURE_READING,		/**< Zerwano poÄąâ€šĂ„â€¦czenie podczas odczytu */
	GG_FAILURE_WRITING,		/**< Zerwano poÄąâ€šĂ„â€¦czenie podczas zapisu */
	GG_FAILURE_PASSWORD,		/**< NieprawidÄąâ€šowe hasÄąâ€šo */
	GG_FAILURE_404, 		/**< NieuÄąÄ˝ywane */
	GG_FAILURE_TLS,			/**< BÄąâ€šĂ„â€¦d negocjacji szyfrowanego poÄąâ€šĂ„â€¦czenia */
	GG_FAILURE_NEED_EMAIL, 		/**< Serwer rozÄąâ€šĂ„â€¦czyÄąâ€š nas z proÄąâ€şbĂ„â€¦ o zmianĂ„â„˘ adresu e-mail */
	GG_FAILURE_INTRUDER,		/**< Zbyt wiele prÄ‚Ĺ‚b poÄąâ€šĂ„â€¦czenia z nieprawidÄąâ€šowym hasÄąâ€šem */
	GG_FAILURE_UNAVAILABLE,		/**< Serwery sĂ„â€¦ wyÄąâ€šĂ„â€¦czone */
	GG_FAILURE_PROXY,		/**< BÄąâ€šĂ„â€¦d serwera poÄąâ€şredniczĂ„â€¦cego */
	GG_FAILURE_HUB,			/**< BÄąâ€šĂ„â€¦d poÄąâ€šĂ„â€¦czenia z hubem */
	GG_FAILURE_INTERNAL,		/**< BÄąâ€šĂ„â€¦d wewnĂ„â„˘trzny */
};

/**
 * Kod bÄąâ€šĂ„â„˘du danej operacji.
 *
 * Nie zawiera przesadnie szczegÄ‚Ĺ‚Äąâ€šowych informacji o powodach bÄąâ€šĂ„â„˘dÄ‚Ĺ‚w, by nie
 * komplikowaĂ„â€ˇ ich obsÄąâ€šugi. JeÄąâ€şli wymagana jest wiĂ„â„˘ksza dokÄąâ€šadnoÄąâ€şĂ„â€ˇ, naleÄąÄ˝y
 * sprawdziĂ„â€ˇ zawartoÄąâ€şĂ„â€ˇ zmiennej systemowej \c errno.
 */
enum gg_error_t {
	GG_ERROR_RESOLVING = 1,		/**< Nie znaleziono hosta */
	GG_ERROR_CONNECTING,		/**< BÄąâ€šĂ„â€¦d poÄąâ€šĂ„â€¦czenia */
	GG_ERROR_READING,		/**< BÄąâ€šĂ„â€¦d odczytu/odbierania */
	GG_ERROR_WRITING,		/**< BÄąâ€šĂ„â€¦d zapisu/wysyÄąâ€šania */

	GG_ERROR_DCC_HANDSHAKE,		/**< BÄąâ€šĂ„â€¦d negocjacji */
	GG_ERROR_DCC_FILE,		/**< BÄąâ€šĂ„â€¦d odczytu/zapisu pliku */
	GG_ERROR_DCC_EOF,		/**< Przedwczesny koniec pliku */
	GG_ERROR_DCC_NET,		/**< BÄąâ€šĂ„â€¦d wysyÄąâ€šania/odbierania */
	GG_ERROR_DCC_REFUSED, 		/**< PoÄąâ€šĂ„â€¦czenie odrzucone */

	GG_ERROR_DCC7_HANDSHAKE,	/**< BÄąâ€šĂ„â€¦d negocjacji */
	GG_ERROR_DCC7_FILE,		/**< BÄąâ€šĂ„â€¦d odczytu/zapisu pliku */
	GG_ERROR_DCC7_EOF,		/**< Przedwczesny koniec pliku */
	GG_ERROR_DCC7_NET,		/**< BÄąâ€šĂ„â€¦d wysyÄąâ€šania/odbierania */
	GG_ERROR_DCC7_REFUSED, 		/**< PoÄąâ€šĂ„â€¦czenie odrzucone */
	GG_ERROR_DCC7_RELAY,		/**< Problem z serwerem poÄąâ€şredniczĂ„â€¦cym */
};

/**
 * Pole zapytania lub odpowiedzi katalogu publicznego.
 */
struct gg_pubdir50_entry {
	int num;	/**< Numer wyniku */
	char *field;	/**< Nazwa pola */
	char *value;	/**< WartoÄąâ€şĂ„â€ˇ pola */
} /* GG_DEPRECATED */;

/**
 * Zapytanie lub odpowiedÄąĹź katalogu publicznego.
 *
 * Patrz \c gg_pubdir50_t.
 */
struct gg_pubdir50_s {
	int count;	/**< Liczba wynikÄ‚Ĺ‚w odpowiedzi */
	uin_t next;	/**< Numer poczĂ„â€¦tkowy nastĂ„â„˘pnego zapytania */
	int type;	/**< Rodzaj zapytania */
	uint32_t seq;	/**< Numer sekwencyjny */
	struct gg_pubdir50_entry *entries;	/**< Pola zapytania lub odpowiedzi */
	int entries_count;	/**< Liczba pÄ‚Ĺ‚l */
} /* GG_DEPRECATED */;

/**
 * Zapytanie lub odpowiedÄąĹź katalogu publicznego.
 *
 * Do pÄ‚Ĺ‚l nie naleÄąÄ˝y siĂ„â„˘ odwoÄąâ€šywaĂ„â€ˇ bezpoÄąâ€şrednio -- wszystkie niezbĂ„â„˘dne
 * informacje sĂ„â€¦ dostĂ„â„˘pne za pomocĂ„â€¦ funkcji \c gg_pubdir50_*
 */
typedef struct gg_pubdir50_s *gg_pubdir50_t;

/**
 * Opis zdarzeÄąâ€ž \c GG_EVENT_MSG i \c GG_EVENT_MULTILOGON_MSG.
 */
struct gg_event_msg {
	uin_t sender;		/**< Numer nadawcy/odbiorcy */
	int msgclass;		/**< Klasa wiadomoÄąâ€şci */
#ifndef _WIN32
	time_t time;		/**< Czas nadania */
#else
	uint32_t time;		/**< Czas nadania */
#endif
	unsigned char *message;	/**< TreÄąâ€şĂ„â€ˇ wiadomoÄąâ€şci */

	int recipients_count;	/**< Liczba odbiorcÄ‚Ĺ‚w konferencji */
	uin_t *recipients;	/**< Odbiorcy konferencji */

	int formats_length;	/**< DÄąâ€šugoÄąâ€şĂ„â€ˇ informacji o formatowaniu tekstu */
	void *formats;		/**< Informacje o formatowaniu tekstu */
	uint32_t seq;		/**< Numer sekwencyjny wiadomoÄąâ€şci */

	char *xhtml_message;	/**< TreÄąâ€şĂ„â€ˇ wiadomoÄąâ€şci w formacie XHTML */

	uint64_t chat_id;	/**< Identyfikator konferencji lub 0, jeÄąÄ˝eli jest to zwykÄąâ€ša wiadomoÄąâ€şĂ„â€ˇ (11.0) */
	uint64_t flags;		/**< Flagi wiadomoÄąâ€şci (11.0) */
};

/**
 * Opis zdarzenia \c GG_EVENT_NOTIFY_DESCR.
 */
struct gg_event_notify_descr {
	struct gg_notify_reply *notify;	/**< Informacje o liÄąâ€şcie kontaktÄ‚Ĺ‚w */
	char *descr;		/**< Opis status */
};

/**
 * Opis zdarzenia \c GG_EVENT_STATUS.
 */
struct gg_event_status {
	uin_t uin;		/**< Numer Gadu-Gadu */
	uint32_t status;	/**< Nowy status */
	char *descr;		/**< Opis */
};

/**
 * Opis zdarzenia \c GG_EVENT_STATUS60.
 */
struct gg_event_status60 {
	uin_t uin;		/**< Numer Gadu-Gadu */
	int status;		/**< Nowy status */
	uint32_t remote_ip;	/**< Adres IP dla poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich */
	uint16_t remote_port;	/**< Port dla poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich */
	int version;		/**< Wersja protokoÄąâ€šu */
	int image_size;		/**< Maksymalny rozmiar obsÄąâ€šugiwanych obrazkÄ‚Ĺ‚w w KiB */
	char *descr;		/**< Opis statusu */
#ifndef _WIN32
	time_t time;		/**< Czas powrotu */
#else
	uint32_t time;		/**< Czas powrotu */
#endif
};

/**
 * Opis zdarzenia \c GG_EVENT_NOTIFY_REPLY60.
 */
struct gg_event_notify60 {
	uin_t uin;		/**< Numer Gadu-Gadu. W ostatnim elemencie jest rÄ‚Ĺ‚wny 0, a pozostaÄąâ€še pola sĂ„â€¦ niezainicjowane. */
	int status;		/**< Nowy status */
	uint32_t remote_ip;	/**< Adres IP dla poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich */
	uint16_t remote_port;	/**< Port dla poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich */
	int version;		/**< Wersja protokoÄąâ€šu */
	int image_size;		/**< Maksymalny rozmiar obsÄąâ€šugiwanych obrazkÄ‚Ĺ‚w w KiB */
	char *descr;		/**< Opis statusu */
#ifndef _WIN32
	time_t time;		/**< Czas powrotu */
#else
	uint32_t time;		/**< Czas powrotu */
#endif
};

/**
 * Opis zdarzenia \c GG_EVENT_ACK.
 */
struct gg_event_ack {
	uin_t recipient;	/**< Numer odbiorcy */
	int status;		/**< Status dorĂ„â„˘czenia */
	int seq;		/**< Numer sekwencyjny wiadomoÄąâ€şci */
};

/**
 * Opis zdarzenia \c GG_EVENT_ACK110.
 */
struct gg_event_ack110 {
	uint8_t msg_type;	/**< Rodzaj wiadomoÄąâ€şci (0x01 - zwykÄąâ€ša, 0x02 - konferencja) */
	uint32_t seq;		/**< Numer sekwencyjny */
	uint32_t time;		/**< Czas zdarzenia */
};

/**
 * Opis zdarzenia \c GG_EVENT_USERLIST.
 */
struct gg_event_userlist {
	char type;		/**< Rodzaj odpowiedzi */
	char *reply;		/**< TreÄąâ€şĂ„â€ˇ odpowiedzi */
};

/**
 * Opis zdarzenia \c GG_EVENT_DCC_VOICE_DATA.
 */
struct gg_event_dcc_voice_data {
	uint8_t *data;		/**< Dane dÄąĹźwiĂ„â„˘kowe */
	int length;		/**< Rozmiar danych dÄąĹźwiĂ„â„˘kowych */
};

/**
 * Opis zdarzenia \c GG_EVENT_IMAGE_REQUEST.
 */
struct gg_event_image_request {
	uin_t sender;		/**< Nadawca ÄąÄ˝Ă„â€¦dania */
	uint32_t size;		/**< Rozmiar obrazka */
	uint32_t crc32;		/**< Suma kontrolna CRC32 */
};

/**
 * Opis zdarzenia \c GG_EVENT_IMAGE_REPLY.
 */
struct gg_event_image_reply {
	uin_t sender;		/**< Nadawca obrazka */
	uint32_t size;		/**< Rozmiar obrazka */
	uint32_t crc32;		/**< Suma kontrolna CRC32 */
	char *filename;		/**< Nazwa pliku */
	char *image;		/**< Bufor z obrazkiem */
};

/**
 * Opis zdarzenia \c GG_EVENT_XML_EVENT.
 */
struct gg_event_xml_event {
	char *data;		/**< Bufor z komunikatem */
};

/**
 * Opis zdarzenia \c GG_EVENT_JSON_EVENT.
 */
struct gg_event_json_event {
	char *data;		/**< Bufor z komunikatem */
	char *type;		/**< Bufor z typem komunikatu */
};

/**
 * Opis zdarzenia \c GG_EVENT_DCC7_CONNECTED.
 */
struct gg_event_dcc7_connected {
	struct gg_dcc7 *dcc7;	/**< Struktura poÄąâ€šĂ„â€¦czenia */
};

/**
 * Opis zdarzenia \c GG_EVENT_DCC7_PENDING.
 */
struct gg_event_dcc7_pending {
	struct gg_dcc7 *dcc7;	/**< Struktura poÄąâ€šĂ„â€¦czenia */
};

/**
 * Opis zdarzenia \c GG_EVENT_DCC7_REJECT.
 */
struct gg_event_dcc7_reject {
	struct gg_dcc7 *dcc7;	/**< Struktura poÄąâ€šĂ„â€¦czenia */
	int reason;		/**< powÄ‚Ĺ‚d odrzucenia */
};

/**
 * Opis zdarzenia \c GG_EVENT_DCC7_ACCEPT.
 */
struct gg_event_dcc7_accept {
	struct gg_dcc7 *dcc7;	/**< Struktura poÄąâ€šĂ„â€¦czenia */
	int type;		/**< SposÄ‚Ĺ‚b poÄąâ€šĂ„â€¦czenia (P2P, przez serwer) */
	uint32_t remote_ip;	/**< Adres zdalnego klienta */
	uint16_t remote_port;	/**< Port zdalnego klienta */
};

/**
 * Opis zdarzenia \c GG_EVENT_DCC7_DONE.
 */
struct gg_event_dcc7_done {
	struct gg_dcc7 *dcc7;	/**< Struktura poÄąâ€šĂ„â€¦czenia */
};

/**
 * Opis zdarzenia \c GG_EVENT_TYPING_NOTIFICATION.
 */
struct gg_event_typing_notification {
	uin_t uin;		/**< Numer rozmÄ‚Ĺ‚wcy */
	int length;		/**< DÄąâ€šugoÄąâ€şĂ„â€ˇ tekstu */
};

/**
 * Atrybut uÄąÄ˝ytkownika.
 */
struct gg_event_user_data_attr {
	int type;		/**< Typ atrybutu */
	char *key;		/**< Klucz */
	char *value;		/**< WartoÄąâ€şĂ„â€ˇ */
};

/**
 * Struktura opisujĂ„â€¦ca kontakt w zdarzeniu GG_EVENT_USER_DATA.
 */
struct gg_event_user_data_user {
	uin_t uin;		/**< Numer kontaktu */
	size_t attr_count;	/**< Liczba atrybutÄ‚Ĺ‚w */
	struct gg_event_user_data_attr *attrs;	/**< Lista atrybutÄ‚Ĺ‚w */
};

/**
 * Opis zdarzenia \c GG_EVENT_USER_DATA.
 */
struct gg_event_user_data {
	int type;		/**< Rodzaj informacji o kontaktach */
	size_t user_count;	/**< Liczba kontaktÄ‚Ĺ‚w */
	struct gg_event_user_data_user *users;	/**< Lista kontaktÄ‚Ĺ‚w */
};

/**
 * Struktura opisujĂ„â€¦ca sesjĂ„â„˘ multilogowania.
 */
struct gg_multilogon_session {
	gg_multilogon_id_t id;		/**< Identyfikator sesji */
	char *name;			/**< Nazwa sesji (podana w \c gg_login_params.client_version) */
	uint32_t remote_addr;		/**< Adres sesji */
	int status_flags;		/**< Flagi statusu sesji */
	int protocol_features;		/**< Opcje protokolu sesji */
#ifndef _WIN32
	time_t logon_time;		/**< Czas zalogowania */
#else
	uint32_t logon_time;		/**< Czas zalogowania */
#endif
};

/**
 * Opis zdarzenia \c GG_EVENT_MULTILOGON_INFO.
 */
struct gg_event_multilogon_info {
	int count;		/**< Liczba sesji */
	struct gg_multilogon_session *sessions;	/** Lista sesji */
};

/**
 * Opis zdarzenia \c GG_EVENT_USERLIST100_VERSION.
 */
struct gg_event_userlist100_version {
	uint32_t version;		/**< Numer wersji listy kontaktÄ‚Ĺ‚w na serwerze */
};

/**
 * Opis zdarzenia \c GG_EVENT_USERLIST100_REPLY.
 */
struct gg_event_userlist100_reply {
	char type;			/**< Rodzaj odpowiedzi */
	uint32_t version;		/**< Aktualna wersja listy kontaktÄ‚Ĺ‚w na serwerze */
	char format_type;		/**< Typ formatu listy kontaktÄ‚Ĺ‚w (ÄąÄ˝Ă„â€¦dany w \c gg_userlist100_request.format_type) */
	char *reply;			/**< TreÄąâ€şĂ„â€ˇ listy kontaktÄ‚Ĺ‚w w przesyÄąâ€šanej wersji i formacie */
};

/**
 * Opis zdarzenia \c GG_EVENT_IMTOKEN.
 */
struct gg_event_imtoken {
	char *imtoken;			/**< WartoÄąâ€şĂ„â€ˇ IMTOKEN */
};

/**
 * Opis zdarzenia \c GG_EVENT_PONG110.
 */
struct gg_event_pong110 {
#ifndef _WIN32
	time_t time;			/**< Aktualny czas na serwerze */
#else
	uint32_t time;			/**< Aktualny czas na serwerze */
#endif
};

/**
 * Opis zdarzenia \c GG_EVENT_CHAT_INFO.
 */
struct gg_event_chat_info {
	uint64_t id;			/**< Identyfikator konferencji */
	uint32_t version;		/**< Wersja informacji o konferencji */
	uint32_t participants_count;	/**< IloÄąâ€şĂ„â€ˇ uczestnikÄ‚Ĺ‚w */
	uin_t *participants;		/**< Lista uczestnikÄ‚Ĺ‚w */
};

/**
 * Opis zdarzenia \c GG_EVENT_CHAT_INFO_UPDATE.
 */
struct gg_event_chat_info_update {
	uint64_t id;			/**< Identyfikator konferencji */
	uint32_t type;			/**< Typ aktualizacji (\c GG_CHAT_INFO_UPDATE_*) */
	uin_t participant;		/**< Uczestnik, ktÄ‚Ĺ‚rego dotyczy aktualizacja */
	uin_t inviter;			/**< Uczestnik inicjujĂ„â€¦cy aktualizacjĂ„â„˘ (zapraszajĂ„â€¦cy) */
	uint32_t version;		/**< Wersja informacji o konferencji */
	uint32_t time;			/**< Czas zdarzenia */
};

/**
 * Opis zdarzenia \c GG_EVENT_CHAT_CREATED.
 */
struct gg_event_chat_created {
	uint64_t id;			/**< Identyfikator konferencji */
	uint32_t seq;			/**< Numer sekwencyjny */
};

/**
 * Opis zdarzenia \c GG_EVENT_CHAT_INVITE_ACK.
 */
struct gg_event_chat_invite_ack {
	uint64_t id;			/**< Identyfikator konferencji */
	uint32_t seq;			/**< Numer sekwencyjny */
};

/**
 * Unia wszystkich zdarzeÄąâ€ž zwracanych przez funkcje \c gg_watch_fd(), 
 * \c gg_dcc_watch_fd() i \c gg_dcc7_watch_fd().
 *
 * \ingroup events
 */
union gg_event_union {
	enum gg_failure_t failure;	/**< BÄąâ€šĂ„â€¦d poÄąâ€šĂ„â€¦czenia (\c GG_EVENT_CONN_FAILED) */
	struct gg_notify_reply *notify;	/**< Zmiana statusu kontaktÄ‚Ĺ‚w (\c GG_EVENT_NOTIFY) */
	struct gg_event_notify_descr notify_descr;	/**< Zmiana statusu kontaktÄ‚Ĺ‚w (\c GG_EVENT_NOTIFY_DESCR) */
	struct gg_event_status status;	/**< Zmiana statusu kontaktÄ‚Ĺ‚w (\c GG_EVENT_STATUS) */
	struct gg_event_status60 status60;	/**< Zmiana statusu kontaktÄ‚Ĺ‚w (\c GG_EVENT_STATUS60) */
	struct gg_event_notify60 *notify60;	/**< Zmiana statusu kontaktÄ‚Ĺ‚w (\c GG_EVENT_NOTIFY60) */
	struct gg_event_msg msg;	/**< Otrzymano wiadomoÄąâ€şĂ„â€ˇ (\c GG_EVENT_MSG) */
	struct gg_event_ack ack;	/**< Potwierdzenie wiadomoÄąâ€şci (\c GG_EVENT_ACK) */
	struct gg_event_ack110 ack110;	/**< Potwierdzenie wysÄąâ€šania wiadomoÄąâ€şci (11.0) (\c GG_EVENT_ACK110) */
	struct gg_event_image_request image_request;	/**< ÄąÂ»Ă„â€¦danie wysÄąâ€šania obrazka (\c GG_EVENT_IMAGE_REQUEST) */
	struct gg_event_image_reply image_reply;	/**< OdpowiedÄąĹź z obrazkiem (\c GG_EVENT_IMAGE_REPLY) */
	struct gg_event_userlist userlist;	/**< OdpowiedÄąĹź listy kontaktÄ‚Ĺ‚w (\c GG_EVENT_USERLIST) */
	gg_pubdir50_t pubdir50;	/**< OdpowiedÄąĹź katalogu publicznego (\c GG_EVENT_PUBDIR50_*) */
	struct gg_event_xml_event xml_event;	/**< Zdarzenie systemowe (\c GG_EVENT_XML_EVENT) */
	struct gg_event_json_event json_event;	/**< Zdarzenie systemowe (\c GG_EVENT_JSON_EVENT) */
	struct gg_dcc *dcc_new;	/**< Nowe poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (\c GG_EVENT_DCC_NEW) */
	enum gg_error_t dcc_error;	/**< BÄąâ€šĂ„â€¦d poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego (\c GG_EVENT_DCC_ERROR) */
	struct gg_event_dcc_voice_data dcc_voice_data;	/**< Dane poÄąâ€šĂ„â€¦czenia gÄąâ€šosowego (\c GG_EVENT_DCC_VOICE_DATA) */
	struct gg_dcc7 *dcc7_new;	/**< Nowe poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (\c GG_EVENT_DCC7_NEW) */
	enum gg_error_t dcc7_error;	/**< BÄąâ€šĂ„â€¦d poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego (\c GG_EVENT_DCC7_ERROR) */
	struct gg_event_dcc7_connected dcc7_connected;	/**< Informacja o zestawieniu poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego (\c GG_EVENT_DCC7_CONNECTED) */
	struct gg_event_dcc7_pending dcc7_pending;	/**< Trwa prÄ‚Ĺ‚ba poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego (\c GG_EVENT_DCC7_PENDING) */
	struct gg_event_dcc7_reject dcc7_reject;	/**< Odrzucono poÄąâ€šĂ„â€¦czenia bezpoÄąâ€şredniego (\c GG_EVENT_DCC7_REJECT) */
	struct gg_event_dcc7_accept dcc7_accept;	/**< Zaakceptowano poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (\c GG_EVENT_DCC7_ACCEPT) */
	struct gg_event_dcc7_done dcc7_done;	/**< ZakoÄąâ€žczono poÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie (\c GG_EVENT_DCC7_DONE) */
	struct gg_event_typing_notification typing_notification;	/**< Powiadomienie o pisaniu */
	struct gg_event_user_data user_data;	/**< Informacje o kontaktach */
	struct gg_event_msg multilogon_msg;	/**< Inna sesja wysÄąâ€šaÄąâ€ša wiadomoÄąâ€şĂ„â€ˇ (\c GG_EVENT_MULTILOGON_MSG) */
	struct gg_event_multilogon_info multilogon_info;	/**< Informacja o innych sesjach multilogowania (\c GG_EVENT_MULTILOGON_INFO) */
	struct gg_event_userlist100_version userlist100_version;	/**< Informacja o numerze wersji listy kontaktÄ‚Ĺ‚w na serwerze (\c GG_EVENT_USERLIST100_VERSION) */
	struct gg_event_userlist100_reply userlist100_reply;	/**< OdpowiedÄąĹź listy kontaktÄ‚Ĺ‚w (10.0) (\c GG_EVENT_USERLIST100_REPLY) */
	struct gg_event_imtoken imtoken;	/**< CiĂ„â€¦g IMTOKEN (11.0) (\c GG_EVENT_IMTOKEN) */
	struct gg_event_pong110 pong110;	/**< Utrzymanie poÄąâ€šĂ„â€¦czenia (11.0) (\c GG_EVENT_PONG110) */
	struct gg_event_chat_info chat_info;	/**< Informacje o konferencji (11.0) (\c GG_EVENT_CHAT_INFO) */
	struct gg_event_chat_info_update chat_info_update;	/**< Aktualizacja informacji o konferencji (11.0) (\c GG_EVENT_CHAT_INFO_UPDATE) */
	struct gg_event_chat_created chat_created;	/**< Potwierdzenie utworzenia konferencji (11.0) (\c GG_EVENT_CHAT_CREATED) */
	struct gg_event_chat_invite_ack chat_invite_ack;	/**< Potwierdzenie wysÄąâ€šania zaproszenia do konferencji (11.0) (\c GG_EVENT_CHAT_INVITE_ACK) */
};

/**
 * Opis zdarzenia.
 *
 * Zwracany przez funkcje \c gg_watch_fd(), \c gg_dcc_watch_fd()
 * i \c gg_dcc7_watch_fd(). Po przeanalizowaniu naleÄąÄ˝y zwolniĂ„â€ˇ
 * za pomocĂ„â€¦ \c gg_event_free().
 *
 * \ingroup events
 */
struct gg_event {
	int type;			/**< Rodzaj zdarzenia */
	union gg_event_union event;	/**< Informacja o zdarzeniu */
};

struct gg_event *gg_watch_fd(struct gg_session *sess);
void gg_event_free(struct gg_event *e);

int gg_notify_ex(struct gg_session *sess, uin_t *userlist, char *types, int count);
int gg_notify(struct gg_session *sess, uin_t *userlist, int count);
int gg_add_notify_ex(struct gg_session *sess, uin_t uin, char type);
int gg_add_notify(struct gg_session *sess, uin_t uin);
int gg_remove_notify_ex(struct gg_session *sess, uin_t uin, char type);
int gg_remove_notify(struct gg_session *sess, uin_t uin);

struct gg_http *gg_http_connect(const char *hostname, int port, int async, const char *method, const char *path, const char *header);
int gg_http_watch_fd(struct gg_http *h);
void gg_http_stop(struct gg_http *h);
void gg_http_free(struct gg_http *h);

uint32_t gg_pubdir50(struct gg_session *sess, gg_pubdir50_t req);
gg_pubdir50_t gg_pubdir50_new(int type);
int gg_pubdir50_add(gg_pubdir50_t req, const char *field, const char *value);
int gg_pubdir50_seq_set(gg_pubdir50_t req, uint32_t seq);
const char *gg_pubdir50_get(gg_pubdir50_t res, int num, const char *field);
int gg_pubdir50_type(gg_pubdir50_t res);
int gg_pubdir50_count(gg_pubdir50_t res);
uin_t gg_pubdir50_next(gg_pubdir50_t res);
uint32_t gg_pubdir50_seq(gg_pubdir50_t res);
void gg_pubdir50_free(gg_pubdir50_t res);

#ifndef DOXYGEN

#define GG_PUBDIR50_UIN "FmNumber"
#define GG_PUBDIR50_STATUS "FmStatus"
#define GG_PUBDIR50_FIRSTNAME "firstname"
#define GG_PUBDIR50_LASTNAME "lastname"
#define GG_PUBDIR50_NICKNAME "nickname"
#define GG_PUBDIR50_BIRTHYEAR "birthyear"
#define GG_PUBDIR50_CITY "city"
#define GG_PUBDIR50_GENDER "gender"
#define GG_PUBDIR50_GENDER_FEMALE "1"
#define GG_PUBDIR50_GENDER_MALE "2"
#define GG_PUBDIR50_GENDER_SET_FEMALE "2"
#define GG_PUBDIR50_GENDER_SET_MALE "1"
#define GG_PUBDIR50_ACTIVE "ActiveOnly"
#define GG_PUBDIR50_ACTIVE_TRUE "1"
#define GG_PUBDIR50_START "fmstart"
#define GG_PUBDIR50_FAMILYNAME "familyname"
#define GG_PUBDIR50_FAMILYCITY "familycity"

#else

/** 
 * \ingroup pubdir50
 *
 * Rodzaj pola zapytania.
 */
enum {
	GG_PUBDIR50_UIN,	/**< Numer Gadu-Gadu */
	GG_PUBDIR50_STATUS,	/**< Status (tylko wynik wyszukiwania) */
	GG_PUBDIR50_FIRSTNAME,	/**< ImiĂ„â„˘ */
	GG_PUBDIR50_LASTNAME,	/**< Nazwisko */
	GG_PUBDIR50_NICKNAME,	/**< Pseudonim */
	GG_PUBDIR50_BIRTHYEAR,	/**< Rok urodzenia lub przedziaÄąâ€š lat oddzielony spacjĂ„â€¦ */
	GG_PUBDIR50_CITY,	/**< MiejscowoÄąâ€şĂ„â€ˇ */
	GG_PUBDIR50_GENDER,	/**< PÄąâ€šeĂ„â€ˇ */
	GG_PUBDIR50_ACTIVE,	/**< Osoba dostĂ„â„˘pna (tylko wyszukiwanie) */
	GG_PUBDIR50_START,	/**< Numer poczĂ„â€¦tkowy wyszukiwania (tylko wyszukiwanie) */
	GG_PUBDIR50_FAMILYNAME,	/**< Nazwisko rodowe (tylko wysyÄąâ€šanie informacji o sobie) */
	GG_PUBDIR50_FAMILYCITY,	/**< MiejscowoÄąâ€şĂ„â€ˇ pochodzenia (tylko wysyÄąâ€šanie informacji o sobie) */
};

/**
 * \ingroup pubdir50
 *
 * WartoÄąâ€şĂ„â€ˇ pola GG_PUBDIR50_GENDER przy wyszukiwaniu. Brak pola oznacza dowolnĂ„â€¦ pÄąâ€šeĂ„â€ˇ.
 */
enum {
	GG_PUBDIR50_GENDER_FEMALE,	/**< Kobieta */
	GG_PUBDIR50_GENDER_MALE,	/**< MĂ„â„˘ÄąÄ˝czyzna */
};

/**
 * \ingroup pubdir50
 *
 * WartoÄąâ€şĂ„â€ˇ pola GG_PUBDIR50_GENDER przy wysyÄąâ€šaniu informacji o sobie.
 */
enum {
	GG_PUBDIR50_GENDER_SET_FEMALE,	/**< Kobieta */
	GG_PUBDIR50_GENDER_SET_MALE,	/**< MĂ„â„˘ÄąÄ˝czyzna */
};

/**
 * \ingroup pubdir50
 *
 * WartoÄąâ€şĂ„â€ˇ pola GG_PUBDIR50_ACTIVE.
 */
enum {
	GG_PUBDIR50_ACTIVE_TRUE,	/**< Wyszukaj tylko osoby dostĂ„â„˘pne */
};

#endif	/* DOXYGEN */

/**
 * PowÄ‚Ĺ‚d bÄąâ€šĂ„â„˘du operacji na katalogu publicznym.
 *
 * \ingroup http
 */
typedef enum {
	GG_PUBDIR_ERROR_NONE = 0,	/**< Brak bÄąâ€šĂ„â„˘du */
	GG_PUBDIR_ERROR_OTHER,	/**< Nieznany bÄąâ€šĂ„â€¦d */
	GG_PUBDIR_ERROR_TOKEN,	/**< BÄąâ€šĂ„â„˘dny token */
	GG_PUBDIR_ERROR_OLD_PASSWORD,	/**< Niepoprawne stare hasÄąâ€šo */
	GG_PUBDIR_ERROR_NEW_PASSWORD,	/**< Niepoprawne nowe hasÄąâ€šo */
} gg_pubdir_error_t;

/**
 * Wynik operacji na katalogu publicznym.
 *
 * \ingroup http
 */
struct gg_pubdir {
	int success;		/**< Flaga powodzenia operacji */
	uin_t uin;		/**< Otrzymany numer lub 0 w przypadku bÄąâ€šĂ„â„˘du */
	gg_pubdir_error_t error;	/**< PowÄ‚Ĺ‚d bÄąâ€šĂ„â„˘du */
};

int gg_pubdir_watch_fd(struct gg_http *f);
void gg_pubdir_free(struct gg_http *f);

/**
 * Token autoryzacji niektÄ‚Ĺ‚rych operacji HTTP.
 * 
 * \ingroup token
 */
struct gg_token {
	int width;		/**< SzerokoÄąâ€şĂ„â€ˇ obrazka */
	int height;		/**< WysokoÄąâ€şĂ„â€ˇ obrazka */
	int length;		/**< Liczba znakÄ‚Ĺ‚w w tokenie */
	char *tokenid;		/**< Identyfikator tokenu */
};

struct gg_http *gg_token(int async);
int gg_token_watch_fd(struct gg_http *h);
void gg_token_free(struct gg_http *h);

struct gg_http *gg_register3(const char *email, const char *password, const char *tokenid, const char *tokenval, int async);
#ifndef DOXYGEN
#define gg_register_watch_fd gg_pubdir_watch_fd
#define gg_register_free gg_pubdir_free
#endif

struct gg_http *gg_unregister3(uin_t uin, const char *password, const char *tokenid, const char *tokenval, int async);
#ifndef DOXYGEN
#define gg_unregister_watch_fd gg_pubdir_watch_fd
#define gg_unregister_free gg_pubdir_free
#endif

struct gg_http *gg_remind_passwd3(uin_t uin, const char *email, const char *tokenid, const char *tokenval, int async);
#ifndef DOXYGEN
#define gg_remind_passwd_watch_fd gg_pubdir_watch_fd
#define gg_remind_passwd_free gg_pubdir_free
#endif

struct gg_http *gg_change_passwd4(uin_t uin, const char *email, const char *passwd, const char *newpasswd, const char *tokenid, const char *tokenval, int async);
#ifndef DOXYGEN
#define gg_change_passwd_watch_fd gg_pubdir_watch_fd
#define gg_change_passwd_free gg_pubdir_free
#endif

extern int gg_dcc_port;
extern unsigned long gg_dcc_ip;

int gg_dcc_request(struct gg_session *sess, uin_t uin);

struct gg_dcc *gg_dcc_send_file(uint32_t ip, uint16_t port, uin_t my_uin, uin_t peer_uin);
struct gg_dcc *gg_dcc_get_file(uint32_t ip, uint16_t port, uin_t my_uin, uin_t peer_uin);
struct gg_dcc *gg_dcc_voice_chat(uint32_t ip, uint16_t port, uin_t my_uin, uin_t peer_uin);
void gg_dcc_set_type(struct gg_dcc *d, int type);
int gg_dcc_fill_file_info(struct gg_dcc *d, const char *filename);
int gg_dcc_fill_file_info2(struct gg_dcc *d, const char *filename, const char *local_filename);
int gg_dcc_voice_send(struct gg_dcc *d, char *buf, int length);

#define GG_DCC_VOICE_FRAME_LENGTH 195		/**< Rozmiar pakietu gÄąâ€šosowego przed wersjĂ„â€¦ Gadu-Gadu 5.0.5 */
#define GG_DCC_VOICE_FRAME_LENGTH_505 326	/**< Rozmiar pakietu gÄąâ€šosowego od wersji Gadu-Gadu 5.0.5 */

struct gg_dcc *gg_dcc_socket_create(uin_t uin, uint16_t port);
#ifndef DOXYGEN
#define gg_dcc_socket_free gg_dcc_free
#define gg_dcc_socket_watch_fd gg_dcc_watch_fd
#endif

struct gg_event *gg_dcc_watch_fd(struct gg_dcc *d);

void gg_dcc_free(struct gg_dcc *c);

struct gg_event *gg_dcc7_watch_fd(struct gg_dcc7 *d);
struct gg_dcc7 *gg_dcc7_send_file(struct gg_session *sess, uin_t rcpt, const char *filename, const char *filename1250, const char *hash);
struct gg_dcc7 *gg_dcc7_send_file_fd(struct gg_session *sess, uin_t rcpt, int fd, size_t size, const char *filename1250, const char *hash);
int gg_dcc7_accept(struct gg_dcc7 *dcc, unsigned int offset);
int gg_dcc7_reject(struct gg_dcc7 *dcc, int reason);
void gg_dcc7_free(struct gg_dcc7 *d);

extern int gg_debug_level;

extern void (*gg_debug_handler)(int level, const char *format, va_list ap);
extern void (*gg_debug_handler_session)(struct gg_session *sess, int level, const char *format, va_list ap);

extern FILE *gg_debug_file;

/**
 * \ingroup debug
 * @{
 */
#define GG_DEBUG_NET 1		/**< Rejestracja zdarzeÄąâ€ž zwiĂ„â€¦zanych z sieciĂ„â€¦ */
#define GG_DEBUG_TRAFFIC 2	/**< Rejestracja ruchu sieciowego */
#define GG_DEBUG_DUMP 4		/**< Rejestracja zawartoÄąâ€şci pakietÄ‚Ĺ‚w */
#define GG_DEBUG_FUNCTION 8	/**< Rejestracja wywoÄąâ€šaÄąâ€ž funkcji */
#define GG_DEBUG_MISC 16	/**< Rejestracja rÄ‚Ĺ‚ÄąÄ˝nych informacji */
#define GG_DEBUG_VERBOSE 32	/**< Rejestracja informacji szczegÄ‚Ĺ‚Äąâ€šowych */
#define GG_DEBUG_WARNING 64	/**< Rejestracja ostrzeÄąÄ˝eÄąâ€ž */
#define GG_DEBUG_ERROR 128	/**< Rejestracja bÄąâ€šĂ„â„˘dÄ‚Ĺ‚w krytycznych */
/** @} */

const char *gg_debug_state(enum gg_state_t state);
const char *gg_debug_event(enum gg_event_t event);

#ifdef GG_DEBUG_DISABLE
#define gg_debug(...) do { } while (0)
#define gg_debug_session(...) do { } while (0)
#else
void gg_debug(int level, const char *format, ...) GG_GNUC_PRINTF(2, 3);
void gg_debug_session(struct gg_session *sess, int level, const char *format, ...) GG_GNUC_PRINTF(3, 4);
#endif

const char *gg_libgadu_version(void);

/**
 * Lista funkcji biblioteki, ktÄ‚Ĺ‚re zaleÄąÄ˝Ă„â€¦ od zewnĂ„â„˘trznych bibliotek.
 *
 * \ingroup version
 */
typedef enum {
	GG_LIBGADU_FEATURE_SSL,		/**< Biblioteka obsÄąâ€šuguje poÄąâ€šĂ„â€¦czenia szyfrowane */
	GG_LIBGADU_FEATURE_PTHREAD,	/**< Biblioteka obsÄąâ€šuguje rozwiĂ„â€¦zywanie nazw za pomocĂ„â€¦ wĂ„â€¦tkÄ‚Ĺ‚w */
	GG_LIBGADU_FEATURE_USERLIST100,	/**< Biblioteka obsÄąâ€šuguje listĂ„â„˘ kontaktÄ‚Ĺ‚w zgodnĂ„â€¦ z Gadu-Gadu 10 */
} gg_libgadu_feature_t;

int gg_libgadu_check_feature(gg_libgadu_feature_t feature);

extern int gg_proxy_enabled;
extern char *gg_proxy_host;
extern int gg_proxy_port;
extern char *gg_proxy_username;
extern char *gg_proxy_password;
extern int gg_proxy_http_only;

extern unsigned long gg_local_ip;

#define GG_LOGIN_HASH_GG32 0x01	/**< Algorytm Gadu-Gadu */
#define GG_LOGIN_HASH_SHA1 0x02	/**< Algorytm SHA1 */

#ifndef DOXYGEN

#define GG_PUBDIR50_WRITE 0x01
#define GG_PUBDIR50_READ 0x02
#define GG_PUBDIR50_SEARCH 0x03
#define GG_PUBDIR50_SEARCH_REQUEST GG_PUBDIR50_SEARCH
#define GG_PUBDIR50_SEARCH_REPLY 0x05

#else

/**
 * \ingroup pubdir50
 * 
 * Rodzaj zapytania lub odpowiedzi katalogu publicznego.
 */
enum {
	GG_PUBDIR50_WRITE,	/**< WysÄąâ€šanie do serwera informacji o sobie */
	GG_PUBDIR50_READ,	/**< Pobranie z serwera informacji o sobie */
	GG_PUBDIR50_SEARCH,	/**< Wyszukiwanie w katalogu publicznym */
	GG_PUBDIR50_SEARCH_REPLY,	/**< Wynik wyszukiwania w katalogu publicznym */
};

#endif	/* DOXYGEN */

/** \cond obsolete */

#define gg_free_event gg_event_free
#define gg_free_http gg_http_free
#define gg_free_pubdir gg_pubdir_free
#define gg_free_register gg_pubdir_free
#define gg_free_remind_passwd gg_pubdir_free
#define gg_free_dcc gg_dcc_free
#define gg_free_change_passwd gg_pubdir_free

struct gg_search_request {
	int active;
	unsigned int start;
	char *nickname;
	char *first_name;
	char *last_name;
	char *city;
	int gender;
	int min_birth;
	int max_birth;
	char *email;
	char *phone;
	uin_t uin;
} /* GG_DEPRECATED */;

struct gg_search {
	int count;
	struct gg_search_result *results;
} GG_DEPRECATED;

struct gg_search_result {
	uin_t uin;
	char *first_name;
	char *last_name;
	char *nickname;
	int born;
	int gender;
	char *city;
	int active;
} GG_DEPRECATED;

#define GG_GENDER_NONE 0
#define GG_GENDER_FEMALE 1
#define GG_GENDER_MALE 2

struct gg_http *gg_search(const struct gg_search_request *r, int async) GG_DEPRECATED;
int gg_search_watch_fd(struct gg_http *f) GG_DEPRECATED;
void gg_free_search(struct gg_http *f) GG_DEPRECATED;
#define gg_search_free gg_free_search

const struct gg_search_request *gg_search_request_mode_0(char *nickname, char *first_name, char *last_name, char *city, int gender, int min_birth, int max_birth, int active, int start) GG_DEPRECATED;
const struct gg_search_request *gg_search_request_mode_1(char *email, int active, int start) GG_DEPRECATED;
const struct gg_search_request *gg_search_request_mode_2(char *phone, int active, int start) GG_DEPRECATED;
const struct gg_search_request *gg_search_request_mode_3(uin_t uin, int active, int start) GG_DEPRECATED;
void gg_search_request_free(struct gg_search_request *r) GG_DEPRECATED;

struct gg_http *gg_register(const char *email, const char *password, int async) GG_DEPRECATED;
struct gg_http *gg_register2(const char *email, const char *password, const char *qa, int async) GG_DEPRECATED;

struct gg_http *gg_unregister(uin_t uin, const char *password, const char *email, int async) GG_DEPRECATED;
struct gg_http *gg_unregister2(uin_t uin, const char *password, const char *qa, int async) GG_DEPRECATED;

struct gg_http *gg_remind_passwd(uin_t uin, int async) GG_DEPRECATED;
struct gg_http *gg_remind_passwd2(uin_t uin, const char *tokenid, const char *tokenval, int async) GG_DEPRECATED;

struct gg_http *gg_change_passwd(uin_t uin, const char *passwd, const char *newpasswd, const char *newemail, int async) GG_DEPRECATED;
struct gg_http *gg_change_passwd2(uin_t uin, const char *passwd, const char *newpasswd, const char *email, const char *newemail, int async) GG_DEPRECATED;
struct gg_http *gg_change_passwd3(uin_t uin, const char *passwd, const char *newpasswd, const char *qa, int async) GG_DEPRECATED;

struct gg_change_info_request {
	char *first_name;
	char *last_name;
	char *nickname;
	char *email;
	int born;
	int gender;
	char *city;
} /* GG_DEPRECATED */;

struct gg_change_info_request *gg_change_info_request_new(const char *first_name, const char *last_name, const char *nickname, const char *email, int born, int gender, const char *city) GG_DEPRECATED;
void gg_change_info_request_free(struct gg_change_info_request *r) GG_DEPRECATED;

struct gg_http *gg_change_info(uin_t uin, const char *passwd, const struct gg_change_info_request *request, int async) GG_DEPRECATED;
#define gg_change_pubdir_watch_fd gg_pubdir_watch_fd
#define gg_change_pubdir_free gg_pubdir_free
#define gg_free_change_pubdir gg_pubdir_free

struct gg_http *gg_userlist_get(uin_t uin, const char *password, int async) GG_DEPRECATED;
int gg_userlist_get_watch_fd(struct gg_http *f) GG_DEPRECATED;
void gg_userlist_get_free(struct gg_http *f) GG_DEPRECATED;

struct gg_http *gg_userlist_put(uin_t uin, const char *password, const char *contacts, int async) GG_DEPRECATED;
int gg_userlist_put_watch_fd(struct gg_http *f) GG_DEPRECATED;
void gg_userlist_put_free(struct gg_http *f) GG_DEPRECATED;

struct gg_http *gg_userlist_remove(uin_t uin, const char *password, int async) GG_DEPRECATED;
int gg_userlist_remove_watch_fd(struct gg_http *f) GG_DEPRECATED;
void gg_userlist_remove_free(struct gg_http *f) GG_DEPRECATED;

int gg_pubdir50_handle_reply(struct gg_event *e, const char *packet, int length) GG_DEPRECATED;

/** \endcond */

int gg_file_hash_sha1(int fd, uint8_t *result) GG_DEPRECATED;

char *gg_saprintf(const char *format, ...) GG_GNUC_PRINTF(1, 2) GG_DEPRECATED;
char *gg_vsaprintf(const char *format, va_list ap) GG_DEPRECATED;

#define gg_alloc_sprintf gg_saprintf

char *gg_get_line(char **ptr) GG_DEPRECATED;

int gg_connect(void *addr, int port, int async) GG_DEPRECATED;
struct in_addr *gg_gethostbyname(const char *hostname) GG_DEPRECATED;
char *gg_read_line(int sock, char *buf, int length) GG_DEPRECATED;
void gg_chomp(char *line) GG_DEPRECATED;
char *gg_urlencode(const char *str) GG_DEPRECATED;
int gg_http_hash(const char *format, ...) GG_DEPRECATED;
void gg_http_free_fields(struct gg_http *h) GG_DEPRECATED;
int gg_read(struct gg_session *sess, char *buf, int length) GG_DEPRECATED;
int gg_write(struct gg_session *sess, const char *buf, int length) GG_DEPRECATED;
void *gg_recv_packet(struct gg_session *sess) GG_DEPRECATED;
int gg_send_packet(struct gg_session *sess, int type, ...) GG_DEPRECATED;
unsigned int gg_login_hash(const unsigned char *password, unsigned int seed) GG_DEPRECATED;
void gg_login_hash_sha1(const char *password, uint32_t seed, uint8_t *result) GG_DEPRECATED;
uint32_t gg_fix32(uint32_t x);
uint16_t gg_fix16(uint16_t x);
#define fix16 gg_fix16
#define fix32 gg_fix32
char *gg_proxy_auth(void) GG_DEPRECATED;
char *gg_base64_encode(const char *buf) GG_DEPRECATED;
char *gg_base64_decode(const char *buf) GG_DEPRECATED;
int gg_image_queue_remove(struct gg_session *s, struct gg_image_queue *q, int freeq) GG_DEPRECATED;

/**
 * Kolejka odbieranych obrazkÄ‚Ĺ‚w.
 */
struct gg_image_queue {
	uin_t sender;			/**< Nadawca obrazka */
	uint32_t size;			/**< Rozmiar obrazka */
	uint32_t crc32;			/**< Suma kontrolna CRC32 */
	char *filename;			/**< Nazwa pliku */
	char *image;			/**< Bufor z odebranymi danymi */
	uint32_t done;			/**< Rozmiar odebranych danych */

	struct gg_image_queue *next;	/**< Kolejny element listy */

	uint32_t packet_type;		/**< \brief Rodzaj odbieranych pakietÄ‚Ĺ‚w. W niektÄ‚Ĺ‚rych przypadkach (przy multilogowaniu) serwer wysyÄąâ€ša nam dwie kopie obrazka jako dwa rÄ‚Ĺ‚ÄąÄ˝ne typy pakietÄ‚Ĺ‚w */
} GG_DEPRECATED;

int gg_dcc7_handle_id(struct gg_session *sess, struct gg_event *e, const void *payload, int len) GG_DEPRECATED;
int gg_dcc7_handle_new(struct gg_session *sess, struct gg_event *e, const void *payload, int len) GG_DEPRECATED;
int gg_dcc7_handle_info(struct gg_session *sess, struct gg_event *e, const void *payload, int len) GG_DEPRECATED;
int gg_dcc7_handle_accept(struct gg_session *sess, struct gg_event *e, const void *payload, int len) GG_DEPRECATED;
int gg_dcc7_handle_reject(struct gg_session *sess, struct gg_event *e, const void *payload, int len) GG_DEPRECATED;

#define GG_APPMSG_HOST "appmsg.gadu-gadu.pl"
#define GG_APPMSG_PORT 80
#define GG_PUBDIR_HOST "pubdir.gadu-gadu.pl"
#define GG_PUBDIR_PORT 80
#define GG_REGISTER_HOST "register.gadu-gadu.pl"
#define GG_REGISTER_PORT 80
#define GG_REMIND_HOST "retr.gadu-gadu.pl"
#define GG_REMIND_PORT 80
#define GG_RELAY_HOST "relay.gadu-gadu.pl"
#define GG_RELAY_PORT 80

#define GG_DEFAULT_PORT 8074
#define GG_HTTPS_PORT 443
#define GG_HTTP_USERAGENT "Mozilla/4.7 [en] (Win98; I)"

#define GG_PROTOCOL_VERSION_100 0x2e
#define GG_PROTOCOL_VERSION_110 0x40

/* GG_DEPRECATED */
#define GG_DEFAULT_CLIENT_VERSION NULL

#define GG_DEFAULT_PROTOCOL_VERSION GG_PROTOCOL_VERSION_110
#define GG_DEFAULT_TIMEOUT 30
#define GG_HAS_AUDIO_MASK 0x40000000
#define GG_HAS_AUDIO7_MASK 0x20000000
#define GG_ERA_OMNIX_MASK 0x04000000
#define GG_LIBGADU_VERSION "1.12.0-rc3"

#ifndef DOXYGEN

#define GG_FEATURE_MSG77		0x0001
#define GG_FEATURE_STATUS77		0x0002
#define GG_FEATURE_UNKNOWN_4		0x0004
#define GG_FEATURE_UNKNOWN_8		0x0008
#define GG_FEATURE_DND_FFC		0x0010
#define GG_FEATURE_IMAGE_DESCR		0x0020
#define GG_FEATURE_UNKNOWN_40		0x0040
#define GG_FEATURE_UNKNOWN_80		0x0080
#define GG_FEATURE_UNKNOWN_100		0x0100
#define GG_FEATURE_USER_DATA		0x0200
#define GG_FEATURE_MSG_ACK		0x0400
#define GG_FEATURE_UNKNOWN_800		0x0800
#define GG_FEATURE_UNKNOWN_1000		0x1000
#define GG_FEATURE_TYPING_NOTIFICATION	0x2000
#define GG_FEATURE_MULTILOGON		0x4000

/* PoniÄąÄ˝sze makra zostaÄąâ€šy zachowane dla zgodnoÄąâ€şci API */
#define GG_FEATURE_MSG80		0
#define GG_FEATURE_STATUS80		0
#define GG_FEATURE_STATUS80BETA		0

#define GG_FEATURE_ALL			(GG_FEATURE_MSG80 | GG_FEATURE_STATUS80 | GG_FEATURE_DND_FFC | GG_FEATURE_IMAGE_DESCR | GG_FEATURE_UNKNOWN_100 | GG_FEATURE_USER_DATA | GG_FEATURE_MSG_ACK | GG_FEATURE_TYPING_NOTIFICATION)

#else

/** 
 * \ingroup login
 *
 * Flagi opcji protokoÄąâ€šu.
 */
enum {
	GG_FEATURE_MSG77,	/**< Klient ÄąÄ˝yczy sobie otrzymywaĂ„â€ˇ wiadomoÄąâ€şci zgodnie z protokoÄąâ€šem 7.7 */
	GG_FEATURE_STATUS77,	/**< Klient ÄąÄ˝yczy sobie otrzymywaĂ„â€ˇ zmiany stanu zgodnie z protokoÄąâ€šem 7.7 */
	GG_FEATURE_DND_FFC,	/**< Klient obsÄąâ€šuguje statusy "nie przeszkadzaĂ„â€ˇ" i "poGGadaj ze mnĂ„â€¦" */
	GG_FEATURE_IMAGE_DESCR,	/**< Klient obsÄąâ€šuguje opisy graficzne oraz flagĂ„â„˘ \c GG_STATUS80_DESCR_MASK */
};


#endif

#define GG_DEFAULT_DCC_PORT 1550

struct gg_header {
	uint32_t type;			/* typ pakietu */
	uint32_t length;		/* dÄąâ€šugoÄąâ€şĂ„â€ˇ reszty pakietu */
} GG_PACKED;

#define GG_WELCOME 0x0001
#define GG_NEED_EMAIL 0x0014

struct gg_welcome {
	uint32_t key;			/* klucz szyfrowania hasÄąâ€ša */
} GG_PACKED;

#define GG_LOGIN 0x000c

struct gg_login {
	uint32_t uin;			/* mÄ‚Ĺ‚j numerek */
	uint32_t hash;			/* hash hasÄąâ€ša */
	uint32_t status;		/* status na dzieÄąâ€ž dobry */
	uint32_t version;		/* moja wersja klienta */
	uint32_t local_ip;		/* mÄ‚Ĺ‚j adres ip */
	uint16_t local_port;		/* port, na ktÄ‚Ĺ‚rym sÄąâ€šucham */
} GG_PACKED;

#define GG_LOGIN_EXT 0x0013

struct gg_login_ext {
	uint32_t uin;			/* mÄ‚Ĺ‚j numerek */
	uint32_t hash;			/* hash hasÄąâ€ša */
	uint32_t status;		/* status na dzieÄąâ€ž dobry */
	uint32_t version;		/* moja wersja klienta */
	uint32_t local_ip;		/* mÄ‚Ĺ‚j adres ip */
	uint16_t local_port;		/* port, na ktÄ‚Ĺ‚rym sÄąâ€šucham */
	uint32_t external_ip;		/* zewnĂ„â„˘trzny adres ip */
	uint16_t external_port;		/* zewnĂ„â„˘trzny port */
} GG_PACKED;

#define GG_LOGIN60 0x0015

struct gg_login60 {
	uint32_t uin;			/* mÄ‚Ĺ‚j numerek */
	uint32_t hash;			/* hash hasÄąâ€ša */
	uint32_t status;		/* status na dzieÄąâ€ž dobry */
	uint32_t version;		/* moja wersja klienta */
	uint8_t dunno1;			/* 0x00 */
	uint32_t local_ip;		/* mÄ‚Ĺ‚j adres ip */
	uint16_t local_port;		/* port, na ktÄ‚Ĺ‚rym sÄąâ€šucham */
	uint32_t external_ip;		/* zewnĂ„â„˘trzny adres ip */
	uint16_t external_port;		/* zewnĂ„â„˘trzny port */
	uint8_t image_size;		/* maksymalny rozmiar grafiki w KiB */
	uint8_t dunno2;			/* 0xbe */
} GG_PACKED;

#define GG_LOGIN70 0x0019

struct gg_login70 {
	uint32_t uin;			/* mÄ‚Ĺ‚j numerek */
	uint8_t hash_type;		/* rodzaj hashowania hasÄąâ€ša */
	uint8_t hash[64];		/* hash hasÄąâ€ša dopeÄąâ€šniony zerami */
	uint32_t status;		/* status na dzieÄąâ€ž dobry */
	uint32_t version;		/* moja wersja klienta */
	uint8_t dunno1;			/* 0x00 */
	uint32_t local_ip;		/* mÄ‚Ĺ‚j adres ip */
	uint16_t local_port;		/* port, na ktÄ‚Ĺ‚rym sÄąâ€šucham */
	uint32_t external_ip;		/* zewnĂ„â„˘trzny adres ip (???) */
	uint16_t external_port;		/* zewnĂ„â„˘trzny port (???) */
	uint8_t image_size;		/* maksymalny rozmiar grafiki w KiB */
	uint8_t dunno2;			/* 0xbe */
} GG_PACKED;

#define GG_LOGIN_OK 0x0003

#define GG_LOGIN_FAILED 0x0009

#define GG_PUBDIR50_REQUEST 0x0014

struct gg_pubdir50_request {
	uint8_t type;			/* GG_PUBDIR50_* */
	uint32_t seq;			/* czas wysÄąâ€šania zapytania */
} GG_PACKED;

#define GG_PUBDIR50_REPLY 0x000e

struct gg_pubdir50_reply {
	uint8_t type;			/* GG_PUBDIR50_* */
	uint32_t seq;			/* czas wysÄąâ€šania zapytania */
} GG_PACKED;

#define GG_NEW_STATUS 0x0002

#ifndef DOXYGEN

#define GG_STATUS_NOT_AVAIL 0x0001
#define GG_STATUS_NOT_AVAIL_DESCR 0x0015
#define GG_STATUS_FFC 0x0017
#define GG_STATUS_FFC_DESCR 0x0018
#define GG_STATUS_AVAIL 0x0002
#define GG_STATUS_AVAIL_DESCR 0x0004
#define GG_STATUS_BUSY 0x0003
#define GG_STATUS_BUSY_DESCR 0x0005
#define GG_STATUS_DND 0x0021
#define GG_STATUS_DND_DESCR 0x0022
#define GG_STATUS_INVISIBLE 0x0014
#define GG_STATUS_INVISIBLE_DESCR 0x0016
#define GG_STATUS_BLOCKED 0x0006

#define GG_STATUS_GGPLUS 0x0020
#define GG_STATUS_NOT_SET 0x0023
#define GG_STATUS_UNKNOWN 0x0025

#define GG_STATUS_IMAGE_MASK 0x0100
#define GG_STATUS_DESCR_MASK 0x4000
#define GG_STATUS_FRIENDS_MASK 0x8000

#define GG_STATUS_FLAG_UNKNOWN 0x00000001
#define GG_STATUS_FLAG_VIDEO 0x00000002
#define GG_STATUS_FLAG_INHERIT 0x00000020
#define GG_STATUS_FLAG_MOBILE 0x00100000
#define GG_STATUS_FLAG_SPAM 0x00800000

#else

/**
 * Rodzaje statusÄ‚Ĺ‚w uÄąÄ˝ytkownika.
 *
 * \ingroup status
 */
enum {
	GG_STATUS_NOT_AVAIL,		/**< NiedostĂ„â„˘pny */
	GG_STATUS_NOT_AVAIL_DESCR,	/**< NiedostĂ„â„˘pny z opisem */
	GG_STATUS_FFC,			/**< PoGGadaj ze mnĂ„â€¦ */
	GG_STATUS_FFC_DESCR,		/**< PoGGadaj ze mnĂ„â€¦ z opisem */
	GG_STATUS_AVAIL,		/**< DostĂ„â„˘pny */
	GG_STATUS_AVAIL_DESCR,		/**< DostĂ„â„˘pny z opisem */
	GG_STATUS_BUSY,			/**< ZajĂ„â„˘ty */
	GG_STATUS_BUSY_DESCR,		/**< ZajĂ„â„˘ty z opisem */
	GG_STATUS_DND,			/**< Nie przeszkadzaĂ„â€ˇ */
	GG_STATUS_DND_DESCR,		/**< Nie przeszakdzaĂ„â€ˇ z opisem */
	GG_STATUS_INVISIBLE,		/**< Niewidoczny (tylko wÄąâ€šasny status) */
	GG_STATUS_INVISIBLE_DESCR,	/**< Niewidoczny z opisem (tylko wÄąâ€šasny status) */
	GG_STATUS_BLOCKED,		/**< Zablokowany (tylko status innych) */
	GG_STATUS_GGPLUS,		/**< Status "Korzystam z GG Plus" */
	GG_STATUS_NOT_SET,		/**< Status nie ustawiony (przy logowaniu siĂ„â„˘ do sieci) */
	GG_STATUS_IMAGE_MASK,		/**< Flaga bitowa oznaczajĂ„â€¦ca opis graficzny (tylko jeÄąâ€şli wybrano \c GG_FEATURE_IMAGE_DESCR) */
	GG_STATUS_DESCR_MASK,		/**< Flaga bitowa oznaczajĂ„â€¦ca status z opisem (tylko jeÄąâ€şli wybrano \c GG_FEATURE_IMAGE_DESCR) */
	GG_STATUS_FRIENDS_MASK,		/**< Flaga bitowa dostĂ„â„˘pnoÄąâ€şci tylko dla znajomych */
};

/**
 * Rodzaje statusÄ‚Ĺ‚w uÄąÄ˝ytkownika. Mapa bitowa.
 *
 * \ingroup status
 */
enum {
	GG_STATUS_FLAG_UNKNOWN,		/**< Przeznaczenie nieznane, ale wystĂ„â„˘puje zawsze */
	GG_STATUS_FLAG_VIDEO,		/**< Klient obsÄąâ€šuguje wideorozmowy */
	GG_STATUS_FLAG_INHERIT,		/**< Synchronizacja statusu do innych klientÄ‚Ĺ‚w (przy logowaniu siĂ„â„˘ do sieci) */
	GG_STATUS_FLAG_MOBILE,		/**< Klient mobilny (ikona telefonu komÄ‚Ĺ‚rkowego) */
	GG_STATUS_FLAG_SPAM,		/**< Klient chce otrzymywaĂ„â€ˇ linki od nieznajomych */
};

#endif	/* DOXYGEN */

/**
 * \ingroup status
 *
 * Flaga bitowa dostepnosci informujaca ze mozemy voipowac
 */

#define GG_STATUS_VOICE_MASK 0x20000	/**< czy ma wlaczone audio (7.7) */

/**
 * \ingroup status
 *
 * Maksymalna dÄąâ€šugoÄąâ€şc opisu.
 */
#define GG_STATUS_DESCR_MAXSIZE 255
#define GG_STATUS_DESCR_MAXSIZE_PRE_8_0 70

#define GG_STATUS_MASK 0xff

/* GG_S_F() tryb tylko dla znajomych */
#define GG_S_F(x) (((x) & GG_STATUS_FRIENDS_MASK) != 0)

/* GG_S() stan bez uwzglĂ„â„˘dnienia dodatkowych flag */
#define GG_S(x) ((x) & GG_STATUS_MASK)


/* GG_S_FF() chĂ„â„˘tny do rozmowy */
#define GG_S_FF(x) (GG_S(x) == GG_STATUS_FFC || GG_S(x) == GG_STATUS_FFC_DESCR)

/* GG_S_AV() dostĂ„â„˘pny */
#define GG_S_AV(x) (GG_S(x) == GG_STATUS_AVAIL || GG_S(x) == GG_STATUS_AVAIL_DESCR)

/* GG_S_AW() zaraz wracam */
#define GG_S_AW(x) (GG_S(x) == GG_STATUS_BUSY || GG_S(x) == GG_STATUS_BUSY_DESCR)

/* GG_S_DD() nie przeszkadzaĂ„â€ˇ */
#define GG_S_DD(x) (GG_S(x) == GG_STATUS_DND || GG_S(x) == GG_STATUS_DND_DESCR)

/* GG_S_NA() niedostĂ„â„˘pny */
#define GG_S_NA(x) (GG_S(x) == GG_STATUS_NOT_AVAIL || GG_S(x) == GG_STATUS_NOT_AVAIL_DESCR)

/* GG_S_I() niewidoczny */
#define GG_S_I(x) (GG_S(x) == GG_STATUS_INVISIBLE || GG_S(x) == GG_STATUS_INVISIBLE_DESCR)


/* GG_S_A() dostĂ„â„˘pny lub chĂ„â„˘tny do rozmowy */
#define GG_S_A(x) (GG_S_FF(x) || GG_S_AV(x))

/* GG_S_B() zajĂ„â„˘ty lub nie przeszkadzaĂ„â€ˇ */
#define GG_S_B(x) (GG_S_AW(x) || GG_S_DD(x))


/* GG_S_D() stan opisowy */
#define GG_S_D(x) (GG_S(x) == GG_STATUS_NOT_AVAIL_DESCR || \
		   GG_S(x) == GG_STATUS_FFC_DESCR || \
		   GG_S(x) == GG_STATUS_AVAIL_DESCR || \
		   GG_S(x) == GG_STATUS_BUSY_DESCR || \
		   GG_S(x) == GG_STATUS_DND_DESCR || \
		   GG_S(x) == GG_STATUS_INVISIBLE_DESCR)

/* GG_S_BL() blokowany lub blokujĂ„â€¦cy */
#define GG_S_BL(x) (GG_S(x) == GG_STATUS_BLOCKED)

/**
 * Zmiana statusu (pakiet \c GG_NEW_STATUS i \c GG_NEW_STATUS80BETA)
 */
struct gg_new_status {
	uint32_t status;			/**< Nowy status */
} GG_PACKED;

#define GG_NOTIFY_FIRST 0x000f
#define GG_NOTIFY_LAST 0x0010

#define GG_NOTIFY 0x0010

struct gg_notify {
	uint32_t uin;				/* numerek danej osoby */
	uint8_t dunno1;				/* rodzaj wpisu w liÄąâ€şcie */
} GG_PACKED;

#ifndef DOXYGEN

#define GG_USER_OFFLINE 0x01
#define GG_USER_NORMAL 0x03
#define GG_USER_BLOCKED 0x04

#else

/**
 * \ingroup contacts
 *
 * Rodzaj kontaktu.
 */
enum {
	GG_USER_NORMAL,		/**< ZwykÄąâ€šy kontakt */
	GG_USER_BLOCKED,	/**< Zablokowany */
	GG_USER_OFFLINE,	/**< Niewidoczny dla kontaktu */
};

#endif	/* DOXYGEN */

#define GG_LIST_EMPTY 0x0012

#define GG_NOTIFY_REPLY 0x000c	/* tak, to samo co GG_LOGIN */

struct gg_notify_reply {
	uint32_t uin;			/* numerek */
	uint32_t status;		/* status danej osoby */
	uint32_t remote_ip;		/* adres ip delikwenta */
	uint16_t remote_port;		/* port, na ktÄ‚Ĺ‚rym sÄąâ€šucha klient */
	uint32_t version;		/* wersja klienta */
	uint16_t dunno2;		/* znowu port? */
} GG_PACKED;

#define GG_NOTIFY_REPLY60 0x0011

struct gg_notify_reply60 {
	uint32_t uin;			/* numerek plus flagi w MSB */
	uint8_t status;			/* status danej osoby */
	uint32_t remote_ip;		/* adres ip delikwenta */
	uint16_t remote_port;		/* port, na ktÄ‚Ĺ‚rym sÄąâ€šucha klient */
	uint8_t version;		/* wersja klienta */
	uint8_t image_size;		/* maksymalny rozmiar grafiki w KiB */
	uint8_t dunno1;			/* 0x00 */
} GG_PACKED;

#define GG_STATUS60 0x000f

struct gg_status60 {
	uint32_t uin;			/* numerek plus flagi w MSB */
	uint8_t status;			/* status danej osoby */
	uint32_t remote_ip;		/* adres ip delikwenta */
	uint16_t remote_port;		/* port, na ktÄ‚Ĺ‚rym sÄąâ€šucha klient */
	uint8_t version;		/* wersja klienta */
	uint8_t image_size;		/* maksymalny rozmiar grafiki w KiB */
	uint8_t dunno1;			/* 0x00 */
} GG_PACKED;

#define GG_NOTIFY_REPLY77 0x0018

struct gg_notify_reply77 {
	uint32_t uin;			/* numerek plus flagi w MSB */
	uint8_t status;			/* status danej osoby */
	uint32_t remote_ip;		/* adres ip delikwenta */
	uint16_t remote_port;		/* port, na ktÄ‚Ĺ‚rym sÄąâ€šucha klient */
	uint8_t version;		/* wersja klienta */
	uint8_t image_size;		/* maksymalny rozmiar grafiki w KiB */
	uint8_t dunno1;			/* 0x00 */
	uint32_t dunno2;		/* ? */
} GG_PACKED;

#define GG_STATUS77 0x0017

struct gg_status77 {
	uint32_t uin;			/* numerek plus flagi w MSB */
	uint8_t status;			/* status danej osoby */
	uint32_t remote_ip;		/* adres ip delikwenta */
	uint16_t remote_port;		/* port, na ktÄ‚Ĺ‚rym sÄąâ€šucha klient */
	uint8_t version;		/* wersja klienta */
	uint8_t image_size;		/* maksymalny rozmiar grafiki w KiB */
	uint8_t dunno1;			/* 0x00 */
	uint32_t dunno2;		/* ? */
} GG_PACKED;

#define GG_ADD_NOTIFY 0x000d
#define GG_REMOVE_NOTIFY 0x000e

struct gg_add_remove {
	uint32_t uin;			/* numerek */
	uint8_t dunno1;			/* bitmapa */
} GG_PACKED;

#define GG_STATUS 0x0002

struct gg_status {
	uint32_t uin;			/* numerek */
	uint32_t status;		/* nowy stan */
} GG_PACKED;

#define GG_SEND_MSG 0x000b

#ifndef DOXYGEN

#define GG_CLASS_QUEUED 0x0001
#define GG_CLASS_OFFLINE GG_CLASS_QUEUED
#define GG_CLASS_MSG 0x0004
#define GG_CLASS_CHAT 0x0008
#define GG_CLASS_CTCP 0x0010
#define GG_CLASS_ACK 0x0020
#define GG_CLASS_EXT GG_CLASS_ACK	/**< Dla kompatybilnoÄąâ€şci wstecz */

#else

/**
 * Klasy wiadomoÄąâ€şci. WartoÄąâ€şci sĂ„â€¦ maskami bitowymi, ktÄ‚Ĺ‚re w wiĂ„â„˘kszoÄąâ€şci
 * przypadkÄ‚Ĺ‚w moÄąÄ˝na Äąâ€šĂ„â€¦czyĂ„â€ˇ (poÄąâ€šĂ„â€¦czenie \c GG_CLASS_MSG i \c GG_CLASS_CHAT
 * nie ma sensu).
 *
 * \ingroup messages
 */
enum {
	GG_CLASS_MSG,		/**< WiadomoÄąâ€şĂ„â€ˇ ma pojawiĂ„â€ˇ siĂ„â„˘ w osobnym oknie */
	GG_CLASS_CHAT,		/**< WiadomoÄąâ€şĂ„â€ˇ ma pojawiĂ„â€ˇ siĂ„â„˘ w oknie rozmowy */
	GG_CLASS_CTCP,		/**< WiadomoÄąâ€şĂ„â€ˇ przeznaczona dla klienta Gadu-Gadu */
	GG_CLASS_ACK,		/**< Klient nie ÄąÄ˝yczy sobie potwierdzenia */
	GG_CLASS_QUEUED,	/**< WiadomoÄąâ€şĂ„â€ˇ zakolejkowana na serwerze (tylko przy odbieraniu) */
};

#endif	/* DOXYGEN */

/**
 * Maksymalna dÄąâ€šugoÄąâ€şĂ„â€ˇ wiadomoÄąâ€şci.
 *
 * \ingroup messages
 */
#define GG_MSG_MAXSIZE 1989

struct gg_send_msg {
	uint32_t recipient;
	uint32_t seq;
	uint32_t msgclass;
} GG_PACKED;

struct gg_msg_richtext {
	uint8_t flag;
	uint16_t length;
} GG_PACKED;

/**
 * Struktura opisujĂ„â€¦ca formatowanie tekstu. W zaleÄąÄ˝noÄąâ€şci od wartoÄąâ€şci pola
 * \c font, zaraz za tĂ„â€¦ strukturĂ„â€¦ moÄąÄ˝e wystĂ„â€¦piĂ„â€ˇ \c gg_msg_richtext_color
 * lub \c gg_msg_richtext_image.
 *
 * \ingroup messages
 */
struct gg_msg_richtext_format {
	uint16_t position;	/**< PoczĂ„â€¦tkowy znak formatowania (liczony od 0) */
	uint8_t font;		/**< Atrybuty formatowania */
} GG_PACKED;

#ifndef DOXYGEN

#define GG_FONT_BOLD 0x01
#define GG_FONT_ITALIC 0x02
#define GG_FONT_UNDERLINE 0x04
#define GG_FONT_COLOR 0x08
#define GG_FONT_IMAGE 0x80

#else

/**
 * Atrybuty formatowania wiadomoÄąâ€şci.
 *
 * \ingroup messages
 */
enum {
	GG_FONT_BOLD,
	GG_FONT_ITALIC,
	GG_FONT_UNDERLINE,
	GG_FONT_COLOR,
	GG_FONT_IMAGE
};

#endif	/* DOXYGEN */

/**
 * Struktura opisujĂ„â€¦cĂ„â€¦ kolor tekstu dla atrybutu \c GG_FONT_COLOR.
 *
 * \ingroup messages
 */
struct gg_msg_richtext_color {
	uint8_t red;		/**< SkÄąâ€šadowa czerwona koloru */
	uint8_t green;		/**< SkÄąâ€šadowa zielona koloru */
	uint8_t blue;		/**< SkÄąâ€šadowa niebieska koloru */
} GG_PACKED;

/**
 * Strukturya opisujĂ„â€¦ca obrazek wstawiony do wiadomoÄąâ€şci dla atrubutu
 * \c GG_FONT_IMAGE.
 *
 * \ingroup messages
 */
struct gg_msg_richtext_image {
	uint16_t unknown1;	/**< Nieznane pole o wartoÄąâ€şci 0x0109 */
	uint32_t size;		/**< Rozmiar obrazka */
	uint32_t crc32;		/**< Suma kontrolna CRC32 obrazka */
} GG_PACKED;

struct gg_msg_recipients {
	uint8_t flag;
	uint32_t count;
} GG_PACKED;

struct gg_msg_image_request {
	uint8_t flag;
	uint32_t size;
	uint32_t crc32;
} GG_PACKED;

struct gg_msg_image_reply {
	uint8_t flag;
	uint32_t size;
	uint32_t crc32;
	/* char filename[]; */
	/* char image[]; */
} GG_PACKED;

#define GG_SEND_MSG_ACK 0x0005

#ifndef DOXYGEN

#define GG_ACK_BLOCKED 0x0001
#define GG_ACK_DELIVERED 0x0002
#define GG_ACK_QUEUED 0x0003
#define GG_ACK_MBOXFULL 0x0004
#define GG_ACK_NOT_DELIVERED 0x0006

#else

/**
 * Status dorĂ„â„˘czenia wiadomoÄąâ€şci.
 *
 * \ingroup messages
 */
enum
{
	GG_ACK_DELIVERED,	/**< WiadomoÄąâ€şĂ„â€ˇ dostarczono. */
	GG_ACK_QUEUED,		/**< WiadomoÄąâ€şĂ„â€ˇ zakolejkowano z powodu niedostĂ„â„˘pnoÄąâ€şci odbiorcy. */
	GG_ACK_BLOCKED,		/**< WiadomoÄąâ€şĂ„â€ˇ zablokowana przez serwer (spam, Äąâ€şwiĂ„â€¦teczne ograniczenia itd.) */
	GG_ACK_MBOXFULL,	/**< WiadomoÄąâ€şci nie dostarczono z powodu zapeÄąâ€šnionej kolejki wiadomoÄąâ€şci odbiorcy. */
	GG_ACK_NOT_DELIVERED	/**< WiadomoÄąâ€şci nie dostarczono (tylko dla \c GG_CLASS_CTCP). */
};

#endif	/* DOXYGEN */

struct gg_send_msg_ack {
	uint32_t status;
	uint32_t recipient;
	uint32_t seq;
} GG_PACKED;

#define GG_RECV_MSG 0x000a

struct gg_recv_msg {
	uint32_t sender;
	uint32_t seq;
	uint32_t time;
	uint32_t msgclass;
} GG_PACKED;

#define GG_PING 0x0008

#define GG_PONG 0x0007

#define GG_DISCONNECTING 0x000b

#define GG_USERLIST_REQUEST 0x0016

#define GG_XML_EVENT 0x0027

#ifndef DOXYGEN

#define GG_USERLIST_PUT 0x00
#define GG_USERLIST_PUT_MORE 0x01
#define GG_USERLIST_GET 0x02

#else

/**
 * \ingroup importexport
 *
 * Rodzaj zapytania.
 */
enum {
	GG_USERLIST_PUT,	/**< Eksport listy kontaktÄ‚Ĺ‚w. */
	GG_USERLIST_GET,	/**< Import listy kontaktÄ‚Ĺ‚w. */
};

#endif	/* DOXYGEN */

struct gg_userlist_request {
	uint8_t type;
} GG_PACKED;

#define GG_USERLIST_REPLY 0x0010

#ifndef DOXYGEN

#define GG_USERLIST_PUT_REPLY 0x00
#define GG_USERLIST_PUT_MORE_REPLY 0x02
#define GG_USERLIST_GET_REPLY 0x06
#define GG_USERLIST_GET_MORE_REPLY 0x04

#else

/**
 * \ingroup importexport
 *
 * Rodzaj odpowiedzi.
 */
enum {
	GG_USERLIST_PUT_REPLY,	/**< Wyeksportowano listy kontaktÄ‚Ĺ‚w. */
	GG_USERLIST_GET_REPLY,	/**< Zaimportowano listĂ„â„˘ kontaktÄ‚Ĺ‚w. */
};

#endif	/* DOXYGEN */

struct gg_userlist_reply {
	uint8_t type;
} GG_PACKED;

#ifndef DOXYGEN

#define GG_USERLIST100_PUT 0x00
#define GG_USERLIST100_GET 0x02

#else

/**
 * \ingroup importexport
 *
 * Rodzaj zapytania (10.0).
 */
enum {
	GG_USERLIST100_PUT,	/**< Eksport listy kontaktÄ‚Ĺ‚w. */
	GG_USERLIST100_GET,	/**< Import listy kontaktÄ‚Ĺ‚w. */
};

#endif	/* DOXYGEN */

#ifndef DOXYGEN

#define GG_USERLIST100_FORMAT_TYPE_NONE 0x00
#define GG_USERLIST100_FORMAT_TYPE_GG70 0x01
#define GG_USERLIST100_FORMAT_TYPE_GG100 0x02

#else

/**
 * \ingroup importexport
 *
 * Typ formatu listy kontaktÄ‚Ĺ‚w (10.0).
 */
enum {
	GG_USERLIST100_FORMAT_TYPE_NONE,	/**< Brak treÄąâ€şci listy kontaktÄ‚Ĺ‚w. */
	GG_USERLIST100_FORMAT_TYPE_GG70,	/**< Format listy kontaktÄ‚Ĺ‚w zgodny z Gadu-Gadu 7.0. */
	GG_USERLIST100_FORMAT_TYPE_GG100,	/**< Format listy kontaktÄ‚Ĺ‚w zgodny z Gadu-Gadu 10.0. */
};

#endif	/* DOXYGEN */

#ifndef DOXYGEN

#define GG_USERLIST100_REPLY_LIST 0x00
#define GG_USERLIST100_REPLY_UPTODATE 0x01
#define GG_USERLIST100_REPLY_ACK 0x10
#define GG_USERLIST100_REPLY_REJECT 0x12

#else

/**
 * \ingroup importexport
 *
 * Typ odpowiedzi listy kontaktÄ‚Ĺ‚w (10.0).
 */
enum {
	GG_USERLIST100_REPLY_LIST,	/**< W odpowiedzi znajduje siĂ„â„˘ aktualna lista kontaktÄ‚Ĺ‚w na serwerze. */
	GG_USERLIST100_REPLY_UPTODATE,	/**< Komunikat o tym, ÄąÄ˝e lista kontaktÄ‚Ĺ‚w jest juÄąÄ˝ zsynchronizowana. */
	GG_USERLIST100_REPLY_ACK,	/**< Potwierdzenie odebrania nowej wersji listy kontaktÄ‚Ĺ‚w. W polu \c gg_userlist100_reply.version znajduje siĂ„â„˘ numer nowej wersji listy kontaktÄ‚Ĺ‚w. */
	GG_USERLIST100_REPLY_REJECT,	/**< Odmowa przyjĂ„â„˘cia nowej wersji listy kontaktÄ‚Ĺ‚w. W polu \c gg_userlist100_reply.version znajduje siĂ„â„˘ numer wersji listy kontaktÄ‚Ĺ‚w aktualnie przechowywanej przez serwer. */
};

#endif /* DOXYGEN */

struct gg_dcc_tiny_packet {
	uint8_t type;		/* rodzaj pakietu */
} GG_PACKED;

struct gg_dcc_small_packet {
	uint32_t type;		/* rodzaj pakietu */
} GG_PACKED;

struct gg_dcc_big_packet {
	uint32_t type;		/* rodzaj pakietu */
	uint32_t dunno1;		/* niewiadoma */
	uint32_t dunno2;		/* niewiadoma */
} GG_PACKED;

/*
 * pÄ‚Ĺ‚ki co, nie znamy dokÄąâ€šadnie protokoÄąâ€šu. nie wiemy, co czemu odpowiada.
 * nazwy sĂ„â€¦ niepowaÄąÄ˝ne i tymczasowe.
 */
#define GG_DCC_WANT_FILE 0x0003		/* peer chce plik */
#define GG_DCC_HAVE_FILE 0x0001		/* wiĂ„â„˘c mu damy */
#define GG_DCC_HAVE_FILEINFO 0x0003	/* niech ma informacje o pliku */
#define GG_DCC_GIMME_FILE 0x0006	/* peer jest pewny */
#define GG_DCC_CATCH_FILE 0x0002	/* wysyÄąâ€šamy plik */

#define GG_DCC_FILEATTR_READONLY 0x0020

#define GG_DCC_TIMEOUT_SEND 1800	/* 30 minut */
#define GG_DCC_TIMEOUT_GET 1800		/* 30 minut */
#define GG_DCC_TIMEOUT_FILE_ACK 300	/* 5 minut */
#define GG_DCC_TIMEOUT_VOICE_ACK 300	/* 5 minut */

#define GG_DCC7_INFO 0x1f

struct gg_dcc7_info {
	uint32_t uin;			/* numer nadawcy */
	uint32_t type;			/* sposÄ‚Ĺ‚b poÄąâ€šĂ„â€¦czenia */
	gg_dcc7_id_t id;		/* identyfikator poÄąâ€šĂ„â€¦czenia */
	char info[GG_DCC7_INFO_LEN];	/* informacje o poÄąâ€šĂ„â€¦czeniu "ip port" */
	char hash[GG_DCC7_INFO_HASH_LEN];/* skrÄ‚Ĺ‚t "ip" */
} GG_PACKED;

#define GG_DCC7_NEW 0x20

struct gg_dcc7_new {
	gg_dcc7_id_t id;		/* identyfikator poÄąâ€šĂ„â€¦czenia */
	uint32_t uin_from;		/* numer nadawcy */
	uint32_t uin_to;		/* numer odbiorcy */
	uint32_t type;			/* rodzaj transmisji */
	unsigned char filename[GG_DCC7_FILENAME_LEN];	/* nazwa pliku */
	uint32_t size;			/* rozmiar pliku */
	uint32_t size_hi;		/* rozmiar pliku (starsze bajty) */
	unsigned char hash[GG_DCC7_HASH_LEN];	/* hash SHA1 */
} GG_PACKED;

#define GG_DCC7_ACCEPT 0x21

struct gg_dcc7_accept {
	uint32_t uin;			/* numer przyjmujĂ„â€¦cego poÄąâ€šĂ„â€¦czenie */
	gg_dcc7_id_t id;		/* identyfikator poÄąâ€šĂ„â€¦czenia */
	uint32_t offset;		/* offset przy wznawianiu transmisji */
	uint32_t dunno1;		/* 0x00000000 */
} GG_PACKED;

/* XXX API */
#define GG_DCC7_TYPE_P2P 0x00000001	/**< PoÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie */
#define GG_DCC7_TYPE_SERVER 0x00000002	/**< PoÄąâ€šĂ„â€¦czenie przez serwer */

#define GG_DCC7_REJECT 0x22

struct gg_dcc7_reject {
	uint32_t uin;			/**< Numer odrzucajĂ„â€¦cego poÄąâ€šĂ„â€¦czenie */
	gg_dcc7_id_t id;		/**< Identyfikator poÄąâ€šĂ„â€¦czenia */
	uint32_t reason;		/**< PowÄ‚Ĺ‚d rozÄąâ€šĂ„â€¦czenia */
} GG_PACKED;

/* XXX API */
#define GG_DCC7_REJECT_BUSY 0x00000001	/**< PoÄąâ€šĂ„â€¦czenie bezpoÄąâ€şrednie juÄąÄ˝ trwa, nie umiem obsÄąâ€šuÄąÄ˝yĂ„â€ˇ wiĂ„â„˘cej */
#define GG_DCC7_REJECT_USER 0x00000002	/**< UÄąÄ˝ytkownik odrzuciÄąâ€š poÄąâ€šĂ„â€¦czenie */
#define GG_DCC7_REJECT_VERSION 0x00000006	/**< Druga strona ma wersjĂ„â„˘ klienta nieobsÄąâ€šugujĂ„â€¦cĂ„â€¦ poÄąâ€šĂ„â€¦czeÄąâ€ž bezpoÄąâ€şrednich tego typu */

#define GG_DCC7_ID_REQUEST 0x23

struct gg_dcc7_id_request {
	uint32_t type;			/**< Rodzaj tranmisji */
} GG_PACKED;

/* XXX API */
#define GG_DCC7_TYPE_VOICE 0x00000001	/**< Transmisja gÄąâ€šosu */
#define GG_DCC7_TYPE_FILE 0x00000004	/**< transmisja pliku */

#define GG_DCC7_ID_REPLY 0x23

struct gg_dcc7_id_reply {
	uint32_t type;			/** Rodzaj transmisji */
	gg_dcc7_id_t id;		/** Przyznany identyfikator */
} GG_PACKED;

#define GG_DCC7_DUNNO1 0x24

#define GG_DCC7_TIMEOUT_CONNECT 10	/* 10 sekund */
#define GG_DCC7_TIMEOUT_SEND 1800	/* 30 minut */
#define GG_DCC7_TIMEOUT_GET 1800	/* 30 minut */
#define GG_DCC7_TIMEOUT_FILE_ACK 300	/* 5 minut */
#define GG_DCC7_TIMEOUT_VOICE_ACK 300	/* 5 minut */

#define GG_CHAT_INFO_UPDATE_ENTERED 0x01
#define GG_CHAT_INFO_UPDATE_EXITED 0x03

#ifdef __cplusplus
}
#endif

#ifdef _WIN32
#pragma pack(pop)
#endif

#endif /* LIBGADU_LIBGADU_H */

/*
 * Local variables:
 * c-indentation-style: k&r
 * c-basic-offset: 8
 * indent-tabs-mode: notnil
 * End:
 *
 * vim: shiftwidth=8:
 */
