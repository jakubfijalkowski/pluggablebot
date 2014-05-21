/* include/libgadu.h.  Generated from libgadu.h.in by configure.  */
/* $Id$ */

/*
 *  (C) Copyright 2001-2009 Wojtek Kaniewski <wojtekka@irc.pl>
 *                          Robert J. WoĹşny <speedy@ziew.org>
 *                          Arkadiusz MiĹ›kiewicz <arekm@pld-linux.org>
 *                          Tomasz ChiliĹ„ski <chilek@chilan.com>
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
 * \brief GĹ‚Ăłwny plik nagĹ‚Ăłwkowy biblioteki
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
 * Identyfikator poĹ‚Ä…czenia bezpoĹ›redniego Gadu-Gadu 7.x.
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
 * Makro deklarujÄ…ce pola wspĂłlne dla struktur sesji.
 */
#define gg_common_head(x) \
	int fd;			/**< Obserwowany deskryptor */ \
	int check;		/**< Informacja o ĹĽÄ…daniu odczytu/zapisu (patrz \ref gg_check_t) */ \
	int state;		/**< Aktualny stan poĹ‚Ä…czenia (patrz \ref gg_state_t) */ \
	int error;		/**< Kod bĹ‚Ä™du dla \c GG_STATE_ERROR (patrz \ref gg_error_t) */ \
	int type;		/**< Rodzaj sesji (patrz \ref gg_session_t) */ \
	int id;			/**< Identyfikator sesji */ \
	int timeout;		/**< Czas pozostaĹ‚y do zakoĹ„czenia stanu */ \
	int (*callback)(x*); 	/**< Funkcja zwrotna */ \
	void (*destroy)(x*); 	/**< Funkcja zwalniania zasobĂłw */

/**
 * Struktura wspĂłlna dla wszystkich sesji i poĹ‚Ä…czeĹ„. Pozwala na proste
 * rzutowanie niezaleĹĽne od rodzaju poĹ‚Ä…czenia.
 */
struct gg_common {
	gg_common_head(struct gg_common)
};

struct gg_image_queue;

struct gg_dcc7;

struct gg_dcc7_relay;

struct gg_session_private;

/**
 * SposĂłb rozwiÄ…zywania nazw serwerĂłw.
 */
typedef enum {
	GG_RESOLVER_DEFAULT = 0,	/**< DomyĹ›lny sposĂłb rozwiÄ…zywania nazw (jeden z poniĹĽszych) */
	GG_RESOLVER_FORK,		/**< RozwiÄ…zywanie nazw bazujÄ…ce na procesach */
	GG_RESOLVER_PTHREAD,		/**< RozwiÄ…zywanie nazw bazujÄ…ce na wÄ…tkach */
	GG_RESOLVER_CUSTOM,		/**< Funkcje rozwiÄ…zywania nazw dostarczone przed aplikacjÄ™ */
	GG_RESOLVER_WIN32,		/**< RozwiÄ…zywanie nazw bazujÄ…ce na wÄ…tkach Win32 */
	GG_RESOLVER_INVALID = -1	/**< NieprawidĹ‚owy sposĂłb rozwiÄ…zywania nazw (wynik \c gg_session_get_resolver) */
} gg_resolver_t;

/**
 * Rodzaj kodowania znakĂłw.
 */
typedef enum {
	GG_ENCODING_CP1250 = 0,		/**< Kodowanie CP1250 */
	GG_ENCODING_UTF8,		/**< Kodowanie UTF-8 */
	GG_ENCODING_INVALID = -1	/**< NieprawidĹ‚owe kodowanie */
} gg_encoding_t;

/**
 * StopieĹ„ kompatybilnoĹ›ci ze starymi wersjami API.
 */
typedef enum {
	GG_COMPAT_LEGACY = 0,	/**< CaĹ‚kowita kompatybilnoĹ›Ä‡ (nie wyĹ‚Ä…cza ĹĽadnych funkcji) */
	GG_COMPAT_1_12_0 = 1	/**< WyĹ‚Ä…cza: dostarczanie eventĂłw GG_EVENT_ACK, stary format konferencji */
} gg_compat_t;

/**
 * Flaga poĹ‚Ä…czenia szyfrowanego.
 *
 * \ingroup login
 */
typedef enum {
	GG_SSL_DISABLED = 0,	/**< PoĹ‚Ä…czenie SSL wyĹ‚Ä…czone */
	GG_SSL_ENABLED,		/**< PoĹ‚Ä…czenie SSL wĹ‚Ä…czone gdy dostÄ™pne. BĹ‚Ä™dny certyfikat serwera nie powoduje odrzucenia poĹ‚Ä…czenia. */
	GG_SSL_REQUIRED		/**< PoĹ‚Ä…czenie SSL wymagane. BĹ‚Ä™dny certyfikat serwera powoduje odrzucenie poĹ‚Ä…czenia. */
} gg_ssl_t;

/**
 * Sesja Gadu-Gadu.
 *
 * Tworzona przez funkcjÄ™ \c gg_login(), zwalniana przez \c gg_free_session().
 *
 * \ingroup login
 */
struct gg_session {
	gg_common_head(struct gg_session)

	int async;      	/**< Flaga poĹ‚Ä…czenia asynchronicznego */
	int pid;        	/**< Numer procesu rozwiÄ…zujÄ…cego nazwÄ™ serwera */
	int port;       	/**< Port serwera */
	int seq;        	/**< Numer sekwencyjny ostatniej wiadomoĹ›ci */
	int last_pong;  	/**< Czas otrzymania ostatniej ramki utrzymaniowej */
	int last_event;		/**< Czas otrzymania ostatniego pakietu */

	struct gg_event *event;	/**< Zdarzenie po wywoĹ‚aniu \c callback */

	uint32_t proxy_addr;	/**< Adres serwera poĹ›redniczÄ…cego */
	uint16_t proxy_port;	/**< Port serwera poĹ›redniczÄ…cego */

	uint32_t hub_addr;	/**< Adres huba po rozwiÄ…zaniu nazwy */
	uint32_t server_addr;	/**< Adres serwera otrzymany od huba */

	uint32_t client_addr;	/**< Adres gniazda dla poĹ‚Ä…czeĹ„ bezpoĹ›rednich */
	uint16_t client_port;	/**< Port gniazda dla poĹ‚Ä…czeĹ„ bezpoĹ›rednich */

	uint32_t external_addr;	/**< Publiczny adres dla poĹ‚Ä…czeĹ„ bezpoĹ›rednich */
	uint16_t external_port;	/**< Publiczny port dla poĹ‚Ä…czeĹ„ bezpoĹ›rednich */

	uin_t uin;		/**< WĹ‚asny numer Gadu-Gadu */
	char *password;		/**< HasĹ‚o (zwalniane po uĹĽyciu) */

	int initial_status;	/**< PoczÄ…tkowy status */
	int status;		/**< Aktualny status */

	char *recv_buf;		/**< Bufor na odbierane pakiety. WskaĹşnik zawsze maksymalnie wyrĂłwnany, tak jak w wyniku dziaĹ‚ania \c malloc(). */
	int recv_done;		/**< Liczba wczytanych bajtĂłw pakietu */
	int recv_left;		/**< Liczba pozostaĹ‚ych do wczytania bajtĂłw pakietu */

	int protocol_version;	/**< Wersja protokoĹ‚u (bez flag) */
	char *client_version;	/**< Wersja klienta */
	int last_sysmsg;	/**< Numer ostatniej wiadomoĹ›ci systemowej */

	char *initial_descr;	/**< PoczÄ…tkowy opis statusu */

	void *resolver;		/**< Dane prywatne procesu lub wÄ…tku rozwiÄ…zujÄ…cego nazwÄ™ serwera */

#ifndef DOXYGEN
	char *header_buf;	/**< Bufor na poczÄ…tek nagĹ‚Ăłwka pakietu (nieaktualne) */
	unsigned int header_done;	/**< Liczba wczytanych bajtĂłw nagĹ‚Ăłwka pakietu (nieaktualne) */
#endif

#ifdef GG_CONFIG_HAVE_OPENSSL
	SSL *ssl;		/**< Struktura TLS */
	SSL_CTX *ssl_ctx;	/**< Kontekst sesji TLS */
#else
	void *ssl;		/**< Struktura TLS */
	void *ssl_ctx;		/**< Kontekst sesji TLS */
#endif

	int image_size;		/**< Maksymalny rozmiar obsĹ‚ugiwanych obrazkĂłw w KiB */

	char *userlist_reply;	/**< Bufor z odbieranÄ… listÄ… kontaktĂłw */

	int userlist_blocks;	/**< Liczba czÄ™Ĺ›ci listy kontaktĂłw */

	struct gg_image_queue *images;	/**< Lista wczytywanych obrazkĂłw */

	int hash_type;		/**< Rodzaj funkcji skrĂłtu hasĹ‚a (\c GG_LOGIN_HASH_GG32 lub \c GG_LOGIN_HASH_SHA1) */

	char *send_buf;		/**< Bufor z danymi do wysĹ‚ania */
	int send_left;		/**< Liczba bajtĂłw do wysĹ‚ania */

	struct gg_dcc7 *dcc7_list;	/**< Lista poĹ‚Ä…czeĹ„ bezpoĹ›rednich skojarzonych z sesjÄ… */
	
	int soft_timeout;	/**< Flaga mĂłwiÄ…ca, ĹĽe po przekroczeniu \c timeout naleĹĽy wywoĹ‚aÄ‡ \c gg_watch_fd() */

	int protocol_flags;	/**< Flagi protokoĹ‚u */

	gg_encoding_t encoding;		/**< Rodzaj kodowania znakĂłw */

	gg_resolver_t resolver_type;	/**< SposĂłb rozwiÄ…zywania nazw serwerĂłw */
	int (*resolver_start)(int *fd, void **private_data, const char *hostname);	/**< Funkcja rozpoczynajÄ…ca rozwiÄ…zywanie nazwy */
	void (*resolver_cleanup)(void **private_data, int force);	/**< Funkcja zwalniajÄ…ca zasoby po rozwiÄ…zaniu nazwy */

	int protocol_features;	/**< Opcje protokoĹ‚u */
	int status_flags;	/**< Flagi statusu */
	int recv_msg_count;	/**< Liczba odebranych wiadomoĹ›ci */

	const char *resolver_host;		/**< Nazwa do rozwiÄ…zania */
	struct in_addr *resolver_result;	/**< Wynik rozwiÄ…zywania nazwy */
	unsigned int resolver_index;		/**< Indeks aktualnie obsĹ‚ugiwanego wyniku rozwiÄ…zywania nazwy */
	unsigned int resolver_count;		/**< Liczba wynikĂłw rozwiÄ…zywania nazwy */

	uint16_t connect_port[2];		/**< Lista portĂłw do poĹ‚Ä…czenia */
	unsigned int connect_index;		/**< Indeks aktualnie obsĹ‚ugiwanego portu */

	char *connect_host;			/**< Adres serwera Gadu-Gadu, z ktĂłrym siÄ™ Ĺ‚Ä…czymy */
	gg_ssl_t ssl_flag;			/**< Flaga poĹ‚Ä…czenia szyfrowanego */

	struct gg_session_private *private_data;	/**< Prywatne dane sesji, nie udostÄ™pnione w API */
};

/**
 * PoĹ‚Ä…czenie HTTP.
 *
 * Tworzone przez \c gg_http_connect(), zwalniane przez \c gg_http_free().
 *
 * \ingroup http
 */
struct gg_http {
	gg_common_head(struct gg_http)

	int async;              /**< Flaga poĹ‚Ä…czenia asynchronicznego */
	int pid;                /**< Identyfikator procesu rozwiÄ…zujÄ…cego nazwÄ™ serwera */
	int port;               /**< Port */

	char *query;            /**< Zapytanie HTTP */
	char *header;           /**< Odebrany nagĹ‚Ăłwek */
	int header_size;        /**< Rozmiar wczytanego nagĹ‚Ăłwka */
	char *body;             /**< Odebrana strona */
	unsigned int body_size; /**< Rozmiar strony */

	void *data;             /**< Dane prywatne usĹ‚ugi HTTP */

	char *user_data;	/**< Dane prywatne uĹĽytkownika (nie sÄ… zwalniane) */

	void *resolver;		/**< Dane prywatne procesu lub wÄ…tku rozwiÄ…zujÄ…cego nazwÄ™ */

	unsigned int body_done;	/**< Liczba odebranych bajtĂłw strony */

	gg_resolver_t resolver_type;	/**< SposĂłb rozwiÄ…zywania nazw serwerĂłw */
	int (*resolver_start)(int *fd, void **private_data, const char *hostname);	/**< Funkcja rozpoczynajÄ…ca rozwiÄ…zywanie nazwy */
	void (*resolver_cleanup)(void **private_data, int force);	/**< Funkcja zwalniajÄ…ca zasoby po rozwiÄ…zaniu nazwy */
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
 * Wykorzystywana przy poĹ‚Ä…czeniach bezpoĹ›rednich do wersji Gadu-Gadu 6.x.
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
 * PoĹ‚Ä…czenie bezpoĹ›rednie do wersji Gadu-Gadu 6.x.
 *
 * Tworzone przez \c gg_dcc_socket_create(), \c gg_dcc_get_file(),
 * \c gg_dcc_send_file() lub \c gg_dcc_voice_chat(), zwalniane przez
 * \c gg_dcc_free().
 *
 * \ingroup dcc6
 */
struct gg_dcc {
	gg_common_head(struct gg_dcc)

	struct gg_event *event;	/**< Zdarzenie po wywoĹ‚aniu \c callback */

	int active;		/**< Flaga poĹ‚Ä…czenia aktywnego (nieuĹĽywana) */
	int port;		/**< Port gniazda nasĹ‚uchujÄ…cego */
	uin_t uin;		/**< WĹ‚asny numer Gadu-Gadu */
	uin_t peer_uin;		/**< Numer Gadu-Gadu drugiej strony poĹ‚Ä…czenia */
	int file_fd;		/**< deskryptor pliku */
	unsigned int offset;	/**< PoĹ‚oĹĽenie w pliku */
	unsigned int chunk_size;
				/**< Rozmiar kawaĹ‚ka pliku */
	unsigned int chunk_offset;
				/**< PoĹ‚oĹĽenie w aktualnym kawaĹ‚ku pliku */
	struct gg_file_info file_info;
				/**< Informacje o pliku */
	int established;	/**< Flaga ustanowienia poĹ‚Ä…czenia */
	char *voice_buf;	/**< Bufor na pakiet poĹ‚Ä…czenia gĹ‚osowego */
	int incoming;		/**< Flaga poĹ‚Ä…czenia przychodzÄ…cego */
	char *chunk_buf;	/**< Bufor na fragment danych */
	uint32_t remote_addr;	/**< Adres drugiej strony */
	uint16_t remote_port;	/**< Port drugiej strony */
};

#define GG_DCC7_HASH_LEN	20	/**< Maksymalny rozmiar skrĂłtu pliku w poĹ‚Ä…czeniach bezpoĹ›renich */
#define GG_DCC7_FILENAME_LEN	255	/**< Maksymalny rozmiar nazwy pliku w poĹ‚Ä…czeniach bezpoĹ›rednich */
#define GG_DCC7_INFO_LEN	32	/**< Maksymalny rozmiar informacji o poĹ‚Ä…czeniach bezpoĹ›rednich */
#define GG_DCC7_INFO_HASH_LEN	32	/**< Maksymalny rozmiar skrĂłtu ip informacji o poĹ‚Ä…czeniach bezpoĹ›rednich */

/**
 * PoĹ‚Ä…czenie bezpoĹ›rednie od wersji Gadu-Gadu 7.x.
 *
 * \ingroup dcc7
 */
struct gg_dcc7 {
	gg_common_head(struct gg_dcc7)

	gg_dcc7_id_t cid;	/**< Identyfikator poĹ‚Ä…czenia */

	struct gg_event *event;	/**< Struktura zdarzenia */

	uin_t uin;		/**< WĹ‚asny numer Gadu-Gadu */
	uin_t peer_uin;		/**< Numer Gadu-Gadu drugiej strony poĹ‚Ä…czenia */

	int file_fd;		/**< Deskryptor przesyĹ‚anego pliku */
	unsigned int offset;	/**< Aktualne poĹ‚oĹĽenie w przesyĹ‚anym pliku */
	unsigned int size;	/**< Rozmiar przesyĹ‚anego pliku */
	unsigned char filename[GG_DCC7_FILENAME_LEN + 1];
				/**< Nazwa przesyĹ‚anego pliku */
	unsigned char hash[GG_DCC7_HASH_LEN];
				/**< SkrĂłt SHA1 przesyĹ‚anego pliku */

	int dcc_type;		/**< Rodzaj poĹ‚Ä…czenia bezpoĹ›redniego */
	int established;	/**< Flaga ustanowienia poĹ‚Ä…czenia */
	int incoming;		/**< Flaga poĹ‚Ä…czenia przychodzÄ…cego */
	int reverse;		/**< Flaga poĹ‚Ä…czenia zwrotnego */

	uint32_t local_addr;	/**< Adres lokalny */
	uint16_t local_port;	/**< Port lokalny */

	uint32_t remote_addr;	/**< Adres drugiej strony */
	uint16_t remote_port;	/**< Port drugiej strony */

	struct gg_session *sess;
				/**< Sesja do ktĂłrej przypisano poĹ‚Ä…czenie */
	struct gg_dcc7 *next;	/**< NastÄ™pne poĹ‚Ä…czenie w liĹ›cie */

	int soft_timeout;	/**< Flaga mĂłwiÄ…ca, ĹĽe po przekroczeniu \c timeout naleĹĽy wywoĹ‚aÄ‡ \c gg_dcc7_watch_fd() */
	int seek;		/**< Flaga mĂłwiÄ…ca, ĹĽe moĹĽna zmieniaÄ‡ poĹ‚oĹĽenie w wysyĹ‚anym pliku */

	void *resolver;		/**< Dane prywatne procesu lub wÄ…tku rozwiÄ…zujÄ…cego nazwÄ™ serwera */

	int relay;		/**< Flaga mĂłwiÄ…ca, ĹĽe laczymy sie przez serwer */
	int relay_index;	/**< Numer serwera poĹ›redniczÄ…cego, do ktĂłrego siÄ™ Ĺ‚Ä…czymy */
	int relay_count;	/**< Rozmiar listy serwerĂłw poĹ›redniczÄ…cych */
	struct gg_dcc7_relay *relay_list;	/**< Lista serwerĂłw poĹ›redniczÄ…cych */
};

/**
 * Rodzaj sesji.
 */
enum gg_session_t {
	GG_SESSION_GG = 1,	/**< PoĹ‚Ä…czenie z serwerem Gadu-Gadu */
	GG_SESSION_HTTP,	/**< PoĹ‚Ä…czenie HTTP */
	GG_SESSION_SEARCH,	/**< Wyszukiwanie w katalogu publicznym (nieaktualne) */
	GG_SESSION_REGISTER,	/**< Rejestracja nowego konta */
	GG_SESSION_REMIND,	/**< Przypominanie hasĹ‚a */
	GG_SESSION_PASSWD,	/**< Zmiana hasĹ‚a */
	GG_SESSION_CHANGE,	/**< Zmiana informacji w katalogu publicznym (nieaktualne) */
	GG_SESSION_DCC,		/**< PoĹ‚Ä…czenie bezpoĹ›rednie (do wersji 6.x) */
	GG_SESSION_DCC_SOCKET,	/**< Gniazdo nasĹ‚uchujÄ…ce (do wersji 6.x) */
	GG_SESSION_DCC_SEND,	/**< WysyĹ‚anie pliku (do wersji 6.x) */
	GG_SESSION_DCC_GET,	/**< Odbieranie pliku (do wersji 6.x) */
	GG_SESSION_DCC_VOICE,	/**< Rozmowa gĹ‚osowa (do wersji 6.x) */
	GG_SESSION_USERLIST_GET,	/**< Import listy kontaktĂłw z serwera (nieaktualne) */
	GG_SESSION_USERLIST_PUT,	/**< Eksport listy kontaktĂłw do serwera (nieaktualne) */
	GG_SESSION_UNREGISTER,	/**< Usuwanie konta */
	GG_SESSION_USERLIST_REMOVE,	/**< Usuwanie listy kontaktĂłw z serwera (nieaktualne) */
	GG_SESSION_TOKEN,	/**< Pobieranie tokenu */
	GG_SESSION_DCC7_SOCKET,	/**< Gniazdo nasĹ‚uchujÄ…ce (od wersji 7.x) */
	GG_SESSION_DCC7_SEND,	/**< WysyĹ‚anie pliku (od wersji 7.x) */
	GG_SESSION_DCC7_GET,	/**< Odbieranie pliku (od wersji 7.x) */
	GG_SESSION_DCC7_VOICE,	/**< Rozmowa gĹ‚osowa (od wersji 7.x) */

	GG_SESSION_USER0 = 256,	/**< Rodzaj zadeklarowany dla uĹĽytkownika */
	GG_SESSION_USER1,	/**< Rodzaj zadeklarowany dla uĹĽytkownika */
	GG_SESSION_USER2,	/**< Rodzaj zadeklarowany dla uĹĽytkownika */
	GG_SESSION_USER3,	/**< Rodzaj zadeklarowany dla uĹĽytkownika */
	GG_SESSION_USER4,	/**< Rodzaj zadeklarowany dla uĹĽytkownika */
	GG_SESSION_USER5,	/**< Rodzaj zadeklarowany dla uĹĽytkownika */
	GG_SESSION_USER6,	/**< Rodzaj zadeklarowany dla uĹĽytkownika */
	GG_SESSION_USER7	/**< Rodzaj zadeklarowany dla uĹĽytkownika */
};

/**
 * Aktualny stan sesji.
 */
enum gg_state_t {
	/* wspĂłlne */
	GG_STATE_IDLE = 0,		/**< Nie dzieje siÄ™ nic */
	GG_STATE_RESOLVING,             /**< Oczekiwanie na rozwiÄ…zanie nazwy serwera */
	GG_STATE_CONNECTING,            /**< Oczekiwanie na poĹ‚Ä…czenie */
	GG_STATE_READING_DATA,		/**< Oczekiwanie na dane */
	GG_STATE_ERROR,			/**< Kod bĹ‚Ä™du w polu \c error */

	/* gg_session */
	GG_STATE_CONNECTING_HUB,	/**< Oczekiwanie na poĹ‚Ä…czenie z hubem */
	GG_STATE_CONNECTING_GG,         /**< Oczekiwanie na poĹ‚Ä…czenie z serwerem */
	GG_STATE_READING_KEY,           /**< Oczekiwanie na klucz */
	GG_STATE_READING_REPLY,         /**< Oczekiwanie na odpowiedĹş serwera */
	GG_STATE_CONNECTED,             /**< PoĹ‚Ä…czono z serwerem */

	/* gg_http */
	GG_STATE_SENDING_QUERY,		/**< WysĹ‚ano zapytanie HTTP */
	GG_STATE_READING_HEADER,	/**< Oczekiwanie na nagĹ‚Ăłwek HTTP */
	GG_STATE_PARSING,               /**< Przetwarzanie danych */
	GG_STATE_DONE,                  /**< PoĹ‚Ä…czenie zakoĹ„czone */

	/* gg_dcc */
	GG_STATE_LISTENING,		/* czeka na poĹ‚Ä…czenia */
	GG_STATE_READING_UIN_1,		/* czeka na uin peera */
	GG_STATE_READING_UIN_2,		/* czeka na swĂłj uin */
	GG_STATE_SENDING_ACK,		/* wysyĹ‚a potwierdzenie dcc */
	GG_STATE_READING_ACK,		/* czeka na potwierdzenie dcc */
	GG_STATE_READING_REQUEST,	/* czeka na komendÄ™ */
	GG_STATE_SENDING_REQUEST,	/* wysyĹ‚a komendÄ™ */
	GG_STATE_SENDING_FILE_INFO,	/* wysyĹ‚a informacje o pliku */
	GG_STATE_READING_PRE_FILE_INFO,	/* czeka na pakiet przed file_info */
	GG_STATE_READING_FILE_INFO,	/* czeka na informacje o pliku */
	GG_STATE_SENDING_FILE_ACK,	/* wysyĹ‚a potwierdzenie pliku */
	GG_STATE_READING_FILE_ACK,	/* czeka na potwierdzenie pliku */
	GG_STATE_SENDING_FILE_HEADER,	/* wysyĹ‚a nagĹ‚Ăłwek pliku */
	GG_STATE_READING_FILE_HEADER,	/* czeka na nagĹ‚Ăłwek */
	GG_STATE_GETTING_FILE,		/* odbiera plik */
	GG_STATE_SENDING_FILE,		/* wysyĹ‚a plik */
	GG_STATE_READING_VOICE_ACK,	/* czeka na potwierdzenie voip */
	GG_STATE_READING_VOICE_HEADER,	/* czeka na rodzaj bloku voip */
	GG_STATE_READING_VOICE_SIZE,	/* czeka na rozmiar bloku voip */
	GG_STATE_READING_VOICE_DATA,	/* czeka na dane voip */
	GG_STATE_SENDING_VOICE_ACK,	/* wysyĹ‚a potwierdzenie voip */
	GG_STATE_SENDING_VOICE_REQUEST,	/* wysyĹ‚a ĹĽÄ…danie voip */
	GG_STATE_READING_TYPE,		/* czeka na typ poĹ‚Ä…czenia */

	/* nowe. bez sensu jest to API. */
	GG_STATE_TLS_NEGOTIATION,	/**< Negocjacja poĹ‚Ä…czenia szyfrowanego */

	GG_STATE_REQUESTING_ID,		/**< Oczekiwanie na nadanie identyfikatora poĹ‚Ä…czenia bezpoĹ›redniego */
	GG_STATE_WAITING_FOR_ACCEPT,	/**< Oczekiwanie na potwierdzenie lub odrzucenie poĹ‚Ä…czenia bezpoĹ›redniego */
	GG_STATE_WAITING_FOR_INFO,	/**< Oczekiwanie na informacje o poĹ‚Ä…czeniu bezpoĹ›rednim */

	GG_STATE_READING_ID,		/**< Odebranie identyfikatora poĹ‚Ä…czenia bezpoĹ›redniego */
	GG_STATE_SENDING_ID,		/**< WysĹ‚ano identyfikator poĹ‚Ä…czenia bezpoĹ›redniego */
	GG_STATE_RESOLVING_GG,		/**< Oczekiwanie na rozwiÄ…zanie nazwy serwera Gadu-Gadu */

	GG_STATE_RESOLVING_RELAY,	/**< Oczekiwanie na rozwiÄ…zanie nazwy serwera poĹ›redniczÄ…cego */
	GG_STATE_CONNECTING_RELAY,	/**< Oczekiwanie na poĹ‚Ä…czenie z serwerem poĹ›redniczÄ…cym */
	GG_STATE_READING_RELAY,		/**< Odbieranie danych */

	GG_STATE_DISCONNECTING,		/**< Oczekiwanie na potwierdzenie rozĹ‚Ä…czenia */

	GG_STATE_CONNECT_HUB,		/**< NawiÄ…zanie poĹ‚Ä…czenia z hubem */
	GG_STATE_CONNECT_PROXY_HUB,
	GG_STATE_CONNECT_GG,		/**< NawiÄ…zanie poĹ‚Ä…czenia z serwerem */
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
 * Informacja o tym, czy biblioteka chce zapisywaÄ‡ i/lub czytaÄ‡
 * z deskryptora. Maska bitowa.
 *
 * \ingroup events
 */
enum gg_check_t {
	GG_CHECK_NONE = 0,		/**< Nie sprawdzaj niczego */
	GG_CHECK_WRITE = 1,		/**< SprawdĹş moĹĽliwoĹ›Ä‡ zapisu */
	GG_CHECK_READ = 2		/**< SprawdĹş moĹĽliwoĹ›Ä‡ odczytu */
};

/**
 * Metody nawiÄ…zywania poĹ‚Ä…czeĹ„ TCP/TLS.
 *
 * \ingroup socketmanager
 */
typedef enum {
	GG_SOCKET_MANAGER_TYPE_INTERNAL = 0, /**< WewnÄ™trzna obsĹ‚uga gniazd (domyĹ›lne). */
	GG_SOCKET_MANAGER_TYPE_TCP, /**< Dostarczona przez aplikacjÄ™ - tylko obsĹ‚uga TCP. */
	GG_SOCKET_MANAGER_TYPE_TLS /**< Dostarczona przez aplikacjÄ™ - obsĹ‚uga zarĂłwno TCP, jak i TLS. */
} gg_socket_manager_type_t;

/**
 * Funkcja dostarczona przez aplikacjÄ™, tworzÄ…ca nowe gniazdo TCP/TLS.
 *
 * Po nawiÄ…zaniu poĹ‚Ä…czenia aplikacja musi wywoĹ‚aÄ‡ gg_socket_manager_connected.
 * JeĹĽeli poĹ‚Ä…czenie jest asynchroniczne, wywoĹ‚anie musi nastÄ…piÄ‡ po wyjĹ›ciu z
 * kontekstu tej funkcji. Dla poĹ‚Ä…czeĹ„ synchronicznych z kolei, musi nastÄ…piÄ‡
 * jeszcze przed wyjĹ›ciem z kontekstu.
 *
 * \param cb_data Dane prywatne aplikacji
 * \param host Nazwa hosta
 * \param port Numer portu
 * \param is_tls Flaga okreĹ›lajÄ…ca, czy ma zostaÄ‡ nawiÄ…zane poĹ‚Ä…czenie TLS
 * \param is_async Flaga okreĹ›lajÄ…ca poĹ‚Ä…czenie asynchroniczne (patrz szczegĂłĹ‚y powyĹĽej)
 * \param priv Dane prywatne biblioteki libgadu (do przekazania do gg_socket_manager_connected)
 *
 * \return Uchwyt gniazda
 *
 * \ingroup socketmanager
 */
typedef void* (*gg_socket_manager_connect_cb_t)(void *cb_data, const char *host, int port, int is_tls, int is_async, void *priv);

/**
 * Niszczy gniazdo i zwalnia wszystkie powiÄ…zane z nim zasoby.
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
 * Funkcja powinna zajmowaÄ‡ siÄ™ obsĹ‚ugÄ… TLS, jeĹĽeli gniazdo jest w takim trybie.
 *
 * \param cb_data Dane prywatne aplikacji
 * \param handle Uchwyt gniazda
 * \param buffer Bufor do zapisu danych
 * \param bufsize Rozmiar bufora
 *
 * \return IloĹ›Ä‡ zapisanych danych, lub -1 (oraz ustawiony errno) w przypadku niepowodzenia
 *
 * \ingroup socketmanager
 */
typedef ssize_t (*gg_socket_manager_read_cb_t)(void *cb_data, void *handle, unsigned char *buffer, size_t bufsize);

/**
 * WysyĹ‚a przez gniazdo dane binarne.
 *
 * Funkcja powinna zajmowaÄ‡ siÄ™ obsĹ‚ugÄ… TLS, jeĹĽeli gniazdo jest w takim trybie.
 *
 * \param cb_data Dane prywatne aplikacji
 * \param handle Uchwyt gniazda
 * \param data Dane do wysĹ‚ania
 * \param length Rozmiar danych
 *
 * \return IloĹ›Ä‡ wysĹ‚anych danych, lub -1 (oraz ustawiony errno) w przypadku niepowodzenia
 *
 * \ingroup socketmanager
 */
typedef ssize_t (*gg_socket_manager_write_cb_t)(void *cb_data, void *handle, const unsigned char *data, size_t length);

/**
 * Struktura opisujÄ…ca funkcje zarzÄ…dzajÄ…ce gniazdami, jeĹĽeli aplikacja sama je
 * obsĹ‚uguje.
 *
 * \ingroup socketmanager
 */
typedef struct {
	void *cb_data; /**< Dane prywatne aplikacji */
	gg_socket_manager_connect_cb_t connect_cb; /**< Funkcja tworzÄ…ca nowe gniazdo */
	gg_socket_manager_close_cb_t close_cb; /**< Funkcja niszczÄ…ca gniazdo */
	gg_socket_manager_read_cb_t read_cb; /**< Funkcja odczytujÄ…ca dane z gniazda */
	gg_socket_manager_write_cb_t write_cb; /**< Funkcja wysyĹ‚ajÄ…ca dane przez gniazdo */
#ifndef DOXYGEN
	void *reserved1;
	void *reserved2;
	void *reserved3;
	void *reserved4;
#endif
} gg_socket_manager_t;

int gg_socket_manager_connected(void *handle, void *priv, int fd);

/**
 * Parametry poĹ‚Ä…czenia z serwerem Gadu-Gadu. Parametry zostaĹ‚y przeniesione
 * do struktury, by uniknÄ…Ä‡ zmian API po rozszerzeniu protokoĹ‚u i dodaniu
 * kolejnych opcji poĹ‚Ä…czenia. CzÄ™Ĺ›Ä‡ parametrĂłw, ktĂłre nie sÄ… juĹĽ aktualne
 * lub nie majÄ… znaczenia, zostaĹ‚a usuniÄ™ta z dokumentacji.
 *
 * \ingroup login
 */
struct gg_login_params {
	uin_t uin;			/**< Numer Gadu-Gadu */
	char *password;			/**< HasĹ‚o */
	int async;			/**< Flaga asynchronicznego poĹ‚Ä…czenia (domyĹ›lnie nie) */
	int status;			/**< PoczÄ…tkowy status uĹĽytkownika (domyĹ›lnie \c GG_STATUS_AVAIL) */
	char *status_descr;		/**< PoczÄ…tkowy opis uĹĽytkownika (domyĹ›lnie brak) */
	uint32_t server_addr;		/**< Adres serwera Gadu-Gadu (domyĹ›lnie pobierany automatycznie) */
	uint16_t server_port;		/**< Port serwera Gadu-Gadu (domyĹ›lnie pobierany automatycznie) */
	uint32_t client_addr;		/**< Adres poĹ‚Ä…czeĹ„ bezpoĹ›rednich (domyĹ›lnie dobierany automatycznie) */
	uint16_t client_port;		/**< Port poĹ‚Ä…czeĹ„ bezpoĹ›rednich (domyĹ›lnie dobierany automatycznie) */
	int protocol_version;		/**< Wersja protokoĹ‚u wysyĹ‚ana do serwera (domyĹ›lnie najnowsza obsĹ‚ugiwana) */
	char *client_version;		/**< Wersja klienta wysyĹ‚ana do serwera (domyĹ›lnie najnowsza znana) */
	int has_audio;			/**< Flaga obsĹ‚ugi poĹ‚Ä…czeĹ„ gĹ‚osowych */
	int last_sysmsg;		/**< Numer ostatnio odebranej wiadomoĹ›ci systemowej */
	uint32_t external_addr;		/**< Adres publiczny dla poĹ‚Ä…czeĹ„ bezpoĹ›rednich (domyĹ›lnie dobierany automatycznie) */
	uint16_t external_port;		/**< Port publiczny dla poĹ‚Ä…czeĹ„ bezpoĹ›rednich (domyĹ›lnie dobierany automatycznie) */
	int tls;			/**< Flaga poĹ‚Ä…czenia szyfrowanego (patrz \ref gg_ssl_t) */
	int image_size;			/**< Maksymalny rozmiar obsĹ‚ugiwanych obrazkĂłw w kilobajtach */
#ifndef DOXYGEN
	int era_omnix;			/**< Flaga udawania klienta Era Omnix (nieaktualna) */
#endif
	int hash_type;			/**< Rodzaj skrĂłtu hasĹ‚a (\c GG_LOGIN_HASH_GG32 lub \c GG_LOGIN_HASH_SHA1, domyĹ›lnie SHA1) */
	gg_encoding_t encoding;		/**< Rodzaj kodowania uĹĽywanego w sesji (domyĹ›lnie CP1250) */
	gg_resolver_t resolver;		/**< SposĂłb rozwiÄ…zywania nazw (patrz \ref build-resolver) */
	int protocol_features;		/**< Opcje protokoĹ‚u (flagi GG_FEATURE_*). */
	int status_flags;		/**< Flagi statusu (flagi GG_STATUS_FLAG_*, patrz \ref status). */

	unsigned int struct_size;	/**< Rozmiar struktury. To pole powinno byÄ‡ inicjowane wartoĹ›ciÄ… sizeof(struct gg_login_params) - w przeciwnym przypadku pola za nim nie bÄ™dÄ… obsĹ‚ugiwane. Pozwala na rozszerzanie struktury bez Ĺ‚amania ABI. */

	gg_compat_t compatibility;	/**< StopieĹ„ kompatybilnoĹ›ci ze starym API. */

	char *connect_host;		/**< Nazwa hosta (oraz opcjonalnie port, podany po dwukropku) serwera Gadu-Gadu (domyĹ›lnie pobierany automatycznie) (patrz pole struct_size). */

	gg_socket_manager_type_t socket_manager_type; /**< Wybrana metoda nawiÄ…zywania poĹ‚Ä…czeĹ„ TCP/TLS (domyĹ›lnie wewnÄ™trzna) */
	gg_socket_manager_t socket_manager; /**< JeĹĽeli wybrano metodÄ™ zewnÄ™trznÄ… - konfiguracja jej */

	char **host_white_list;		/**< Lista zakoĹ„czona wskaĹşnikiem NULL, domen akceptowanych w odpowiedziach od huba (domyĹ›lnie wszystkie do tej pory znane). UĹĽywane tylko przy GG_SSL_REQUIRED. Pusta lista wyĹ‚Ä…cza sprawdzanie. */
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
	GG_EVENT_NONE = 0,		/**< Nie wydarzyĹ‚o siÄ™ nic wartego uwagi */
	GG_EVENT_MSG,			/**< \brief Otrzymano wiadomoĹ›Ä‡. Przekazuje rĂłwnieĹĽ wiadomoĹ›ci systemowe od numeru 0. */
	GG_EVENT_NOTIFY,		/**< \brief Informacja o statusach osĂłb z listy kontaktĂłw (przed 6.0). Zdarzenie naleĹĽy obsĹ‚ugiwaÄ‡, jeĹ›li planuje siÄ™ uĹĽywaÄ‡ protokoĹ‚u w wersji starszej niĹĽ domyĹ›lna. Ostatni element tablicy zawiera uin rĂłwny 0, a pozostaĹ‚e pola sÄ… niezainicjowane. */
	GG_EVENT_NOTIFY_DESCR,		/**< \brief Informacja o statusie opisowym osoby z listy kontaktĂłw (przed 6.0). Zdarzenie naleĹĽy obsĹ‚ugiwaÄ‡, jeĹ›li planuje siÄ™ uĹĽywaÄ‡ protokoĹ‚u w wersji starszej niĹĽ domyĹ›lna. */
	GG_EVENT_STATUS,		/**< \brief Zmiana statusu osoby z listy kontaktĂłw (przed 6.0). Zdarzenie naleĹĽy obsĹ‚ugiwaÄ‡, jeĹ›li planuje siÄ™ uĹĽywaÄ‡ protokoĹ‚u w wersji starszej niĹĽ domyĹ›lna. */
	GG_EVENT_ACK,			/**< Potwierdzenie dorÄ™czenia wiadomoĹ›ci */
	GG_EVENT_PONG,			/**< \brief Utrzymanie poĹ‚Ä…czenia. Obecnie serwer nie wysyĹ‚a juĹĽ do klienta ramek utrzymania poĹ‚Ä…czenia, polega wyĹ‚Ä…cznie na wysyĹ‚aniu ramek przez klienta. */
	GG_EVENT_CONN_FAILED,		/**< \brief Nie udaĹ‚o siÄ™ poĹ‚Ä…czyÄ‡ */
	GG_EVENT_CONN_SUCCESS,		/**< \brief PoĹ‚Ä…czono z serwerem. PierwszÄ… rzeczÄ…, jakÄ… naleĹĽy zrobiÄ‡ jest wysĹ‚anie listy kontaktĂłw. */
	GG_EVENT_DISCONNECT,		/**< \brief Serwer zrywa poĹ‚Ä…czenie. Zdarza siÄ™, gdy rĂłwnolegle do serwera podĹ‚Ä…czy siÄ™ druga sesja i trzeba zerwaÄ‡ poĹ‚Ä…czenie z pierwszÄ…. */

	GG_EVENT_DCC_NEW,		/**< Nowe poĹ‚Ä…czenie bezpoĹ›rednie (6.x) */
	GG_EVENT_DCC_ERROR,		/**< BĹ‚Ä…d poĹ‚Ä…czenia bezpoĹ›redniego (6.x) */
	GG_EVENT_DCC_DONE,		/**< ZakoĹ„czono poĹ‚Ä…czenie bezpoĹ›rednie (6.x) */
	GG_EVENT_DCC_CLIENT_ACCEPT,	/**< Moment akceptacji klienta w poĹ‚Ä…czeniu bezpoĹ›rednim (6.x) */
	GG_EVENT_DCC_CALLBACK,		/**< Zwrotne poĹ‚Ä…czenie bezpoĹ›rednie (6.x) */
	GG_EVENT_DCC_NEED_FILE_INFO,	/**< NaleĹĽy wypeĹ‚niÄ‡ \c file_info dla poĹ‚Ä…czenia bezpoĹ›redniego (6.x) */
	GG_EVENT_DCC_NEED_FILE_ACK,	/**< Czeka na potwierdzenie pliku w poĹ‚Ä…czeniu bezpoĹ›rednim (6.x) */
	GG_EVENT_DCC_NEED_VOICE_ACK,	/**< Czeka na potwierdzenie rozmowy w poĹ‚Ä…czeniu bezpoĹ›rednim (6.x) */
	GG_EVENT_DCC_VOICE_DATA, 	/**< Dane bezpoĹ›redniego poĹ‚Ä…czenia gĹ‚osowego (6.x) */

	GG_EVENT_PUBDIR50_SEARCH_REPLY,	/**< OdpowiedĹş katalogu publicznego */
	GG_EVENT_PUBDIR50_READ,		/**< Odczytano wĹ‚asne dane z katalogu publicznego */
	GG_EVENT_PUBDIR50_WRITE,	/**< Zmieniono wĹ‚asne dane w katalogu publicznym */

	GG_EVENT_STATUS60,		/**< Zmiana statusu osoby z listy kontaktĂłw */
	GG_EVENT_NOTIFY60,		/**< Informacja o statusach osĂłb z listy kontaktĂłw. Ostatni element tablicy zawiera uin rĂłwny 0, a pozostaĹ‚e pola sÄ… niezainicjowane.  */
	GG_EVENT_USERLIST,		/**< Wynik importu lub eksportu listy kontaktĂłw */
	GG_EVENT_IMAGE_REQUEST,		/**< Ĺ»Ä…danie przesĹ‚ania obrazka z wiadomoĹ›ci */
	GG_EVENT_IMAGE_REPLY,		/**< PrzysĹ‚ano obrazek z wiadomoĹ›ci */
	GG_EVENT_DCC_ACK,		/**< Potwierdzenie transmisji w poĹ‚Ä…czeniu bezpoĹ›rednim (6.x) */

	GG_EVENT_DCC7_NEW,		/**< Nowe poĹ‚Ä…czenie bezpoĹ›rednie (7.x) */
	GG_EVENT_DCC7_ACCEPT,		/**< Zaakceptowano poĹ‚Ä…czenie bezpoĹ›rednie (7.x), nowy deskryptor */
	GG_EVENT_DCC7_REJECT,		/**< Odrzucono poĹ‚Ä…czenie bezpoĹ›rednie (7.x) */
	GG_EVENT_DCC7_CONNECTED,	/**< Zestawiono poĹ‚Ä…czenie bezpoĹ›rednie (7.x), nowy deskryptor */
	GG_EVENT_DCC7_ERROR,		/**< BĹ‚Ä…d poĹ‚Ä…czenia bezpoĹ›redniego (7.x) */
	GG_EVENT_DCC7_DONE,		/**< ZakoĹ„czono poĹ‚Ä…czenie bezpoĹ›rednie (7.x) */
	GG_EVENT_DCC7_PENDING,		/**< Trwa prĂłba poĹ‚Ä…czenia bezpoĹ›redniego (7.x), nowy deskryptor */

	GG_EVENT_XML_EVENT,		/**< Otrzymano komunikat systemowy (7.7) */
	GG_EVENT_DISCONNECT_ACK,	/**< \brief Potwierdzenie zakoĹ„czenia sesji. Informuje o tym, ĹĽe zmiana stanu na niedostÄ™pny z opisem dotarĹ‚a do serwera i moĹĽna zakoĹ„czyÄ‡ poĹ‚Ä…czenie TCP. */
	GG_EVENT_TYPING_NOTIFICATION,	/**< Powiadomienie o pisaniu */
	GG_EVENT_USER_DATA,		/**< Informacja o kontaktach */
	GG_EVENT_MULTILOGON_MSG,	/**< WiadomoĹ›Ä‡ wysĹ‚ana z innej sesji multilogowania */
	GG_EVENT_MULTILOGON_INFO,	/**< Informacja o innych sesjach multilogowania */

	GG_EVENT_USERLIST100_VERSION,	/**< Otrzymano numer wersji listy kontaktĂłw na serwerze (10.0) */
	GG_EVENT_USERLIST100_REPLY,	/**< Wynik importu lub eksportu listy kontaktĂłw (10.0) */

	GG_EVENT_IMTOKEN,		/**< Otrzymano ciÄ…g IMTOKEN (11.0) */
	GG_EVENT_PONG110,		/**< \brief Utrzymanie poĹ‚Ä…czenia (11.0). MoĹĽe sĹ‚uĹĽyÄ‡ do synchronizacji czasu z serwerem. */
	GG_EVENT_JSON_EVENT,		/**< Otrzymano komunikat systemowy (11.0) */
	GG_EVENT_ACK110,		/**< Potwierdzenie wysĹ‚ania wiadomoĹ›ci (11.0) */

	GG_EVENT_CHAT_INFO,		/**< Otrzymano informacjÄ™ o konferencji (11.0). */
	GG_EVENT_CHAT_INFO_GOT_ALL,	/**< \brief Informacje o wszystkich konferencjach zostaĹ‚y juĹĽ wysĹ‚ane (11.0). Otrzymywany po ostatnim pakiecie \c GG_EVENT_CHAT_INFO */
	GG_EVENT_CHAT_INFO_UPDATE,	/**< \brief Aktualizacja informacji o konferencji (11.0). Dodanie, usuniÄ™cie jednego z uczestnikĂłw. */
	GG_EVENT_CHAT_CREATED,		/**< Potwierdzenie utworzenia konferencji (11.0) */
	GG_EVENT_CHAT_INVITE_ACK,	/**< Potwierdzenie wysĹ‚ania zaproszenia do konferencji (11.0) */
};

#define GG_EVENT_SEARCH50_REPLY GG_EVENT_PUBDIR50_SEARCH_REPLY

/**
 * PowĂłd nieudanego poĹ‚Ä…czenia.
 */
enum gg_failure_t {
	GG_FAILURE_RESOLVING = 1,	/**< Nie znaleziono serwera */
	GG_FAILURE_CONNECTING,		/**< BĹ‚Ä…d poĹ‚Ä…czenia */
	GG_FAILURE_INVALID,		/**< Serwer zwrĂłciĹ‚ nieprawidĹ‚owe dane */
	GG_FAILURE_READING,		/**< Zerwano poĹ‚Ä…czenie podczas odczytu */
	GG_FAILURE_WRITING,		/**< Zerwano poĹ‚Ä…czenie podczas zapisu */
	GG_FAILURE_PASSWORD,		/**< NieprawidĹ‚owe hasĹ‚o */
	GG_FAILURE_404, 		/**< NieuĹĽywane */
	GG_FAILURE_TLS,			/**< BĹ‚Ä…d negocjacji szyfrowanego poĹ‚Ä…czenia */
	GG_FAILURE_NEED_EMAIL, 		/**< Serwer rozĹ‚Ä…czyĹ‚ nas z proĹ›bÄ… o zmianÄ™ adresu e-mail */
	GG_FAILURE_INTRUDER,		/**< Zbyt wiele prĂłb poĹ‚Ä…czenia z nieprawidĹ‚owym hasĹ‚em */
	GG_FAILURE_UNAVAILABLE,		/**< Serwery sÄ… wyĹ‚Ä…czone */
	GG_FAILURE_PROXY,		/**< BĹ‚Ä…d serwera poĹ›redniczÄ…cego */
	GG_FAILURE_HUB,			/**< BĹ‚Ä…d poĹ‚Ä…czenia z hubem */
	GG_FAILURE_INTERNAL,		/**< BĹ‚Ä…d wewnÄ™trzny */
};

/**
 * Kod bĹ‚Ä™du danej operacji.
 *
 * Nie zawiera przesadnie szczegĂłĹ‚owych informacji o powodach bĹ‚Ä™dĂłw, by nie
 * komplikowaÄ‡ ich obsĹ‚ugi. JeĹ›li wymagana jest wiÄ™ksza dokĹ‚adnoĹ›Ä‡, naleĹĽy
 * sprawdziÄ‡ zawartoĹ›Ä‡ zmiennej systemowej \c errno.
 */
enum gg_error_t {
	GG_ERROR_RESOLVING = 1,		/**< Nie znaleziono hosta */
	GG_ERROR_CONNECTING,		/**< BĹ‚Ä…d poĹ‚Ä…czenia */
	GG_ERROR_READING,		/**< BĹ‚Ä…d odczytu/odbierania */
	GG_ERROR_WRITING,		/**< BĹ‚Ä…d zapisu/wysyĹ‚ania */

	GG_ERROR_DCC_HANDSHAKE,		/**< BĹ‚Ä…d negocjacji */
	GG_ERROR_DCC_FILE,		/**< BĹ‚Ä…d odczytu/zapisu pliku */
	GG_ERROR_DCC_EOF,		/**< Przedwczesny koniec pliku */
	GG_ERROR_DCC_NET,		/**< BĹ‚Ä…d wysyĹ‚ania/odbierania */
	GG_ERROR_DCC_REFUSED, 		/**< PoĹ‚Ä…czenie odrzucone */

	GG_ERROR_DCC7_HANDSHAKE,	/**< BĹ‚Ä…d negocjacji */
	GG_ERROR_DCC7_FILE,		/**< BĹ‚Ä…d odczytu/zapisu pliku */
	GG_ERROR_DCC7_EOF,		/**< Przedwczesny koniec pliku */
	GG_ERROR_DCC7_NET,		/**< BĹ‚Ä…d wysyĹ‚ania/odbierania */
	GG_ERROR_DCC7_REFUSED, 		/**< PoĹ‚Ä…czenie odrzucone */
	GG_ERROR_DCC7_RELAY,		/**< Problem z serwerem poĹ›redniczÄ…cym */
};

/**
 * Pole zapytania lub odpowiedzi katalogu publicznego.
 */
struct gg_pubdir50_entry {
	int num;	/**< Numer wyniku */
	char *field;	/**< Nazwa pola */
	char *value;	/**< WartoĹ›Ä‡ pola */
} /* GG_DEPRECATED */;

/**
 * Zapytanie lub odpowiedĹş katalogu publicznego.
 *
 * Patrz \c gg_pubdir50_t.
 */
struct gg_pubdir50_s {
	int count;	/**< Liczba wynikĂłw odpowiedzi */
	uin_t next;	/**< Numer poczÄ…tkowy nastÄ™pnego zapytania */
	int type;	/**< Rodzaj zapytania */
	uint32_t seq;	/**< Numer sekwencyjny */
	struct gg_pubdir50_entry *entries;	/**< Pola zapytania lub odpowiedzi */
	int entries_count;	/**< Liczba pĂłl */
} /* GG_DEPRECATED */;

/**
 * Zapytanie lub odpowiedĹş katalogu publicznego.
 *
 * Do pĂłl nie naleĹĽy siÄ™ odwoĹ‚ywaÄ‡ bezpoĹ›rednio -- wszystkie niezbÄ™dne
 * informacje sÄ… dostÄ™pne za pomocÄ… funkcji \c gg_pubdir50_*
 */
typedef struct gg_pubdir50_s *gg_pubdir50_t;

/**
 * Opis zdarzeĹ„ \c GG_EVENT_MSG i \c GG_EVENT_MULTILOGON_MSG.
 */
struct gg_event_msg {
	uin_t sender;		/**< Numer nadawcy/odbiorcy */
	int msgclass;		/**< Klasa wiadomoĹ›ci */
#ifndef _WIN32
	time_t time;		/**< Czas nadania */
#else
	uint32_t time;		/**< Czas nadania */
#endif
	unsigned char *message;	/**< TreĹ›Ä‡ wiadomoĹ›ci */

	int recipients_count;	/**< Liczba odbiorcĂłw konferencji */
	uin_t *recipients;	/**< Odbiorcy konferencji */

	int formats_length;	/**< DĹ‚ugoĹ›Ä‡ informacji o formatowaniu tekstu */
	void *formats;		/**< Informacje o formatowaniu tekstu */
	uint32_t seq;		/**< Numer sekwencyjny wiadomoĹ›ci */

	char *xhtml_message;	/**< TreĹ›Ä‡ wiadomoĹ›ci w formacie XHTML */

	uint64_t chat_id;	/**< Identyfikator konferencji lub 0, jeĹĽeli jest to zwykĹ‚a wiadomoĹ›Ä‡ (11.0) */
	uint64_t flags;		/**< Flagi wiadomoĹ›ci (11.0) */
};

/**
 * Opis zdarzenia \c GG_EVENT_NOTIFY_DESCR.
 */
struct gg_event_notify_descr {
	struct gg_notify_reply *notify;	/**< Informacje o liĹ›cie kontaktĂłw */
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
	uint32_t remote_ip;	/**< Adres IP dla poĹ‚Ä…czeĹ„ bezpoĹ›rednich */
	uint16_t remote_port;	/**< Port dla poĹ‚Ä…czeĹ„ bezpoĹ›rednich */
	int version;		/**< Wersja protokoĹ‚u */
	int image_size;		/**< Maksymalny rozmiar obsĹ‚ugiwanych obrazkĂłw w KiB */
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
	uin_t uin;		/**< Numer Gadu-Gadu. W ostatnim elemencie jest rĂłwny 0, a pozostaĹ‚e pola sÄ… niezainicjowane. */
	int status;		/**< Nowy status */
	uint32_t remote_ip;	/**< Adres IP dla poĹ‚Ä…czeĹ„ bezpoĹ›rednich */
	uint16_t remote_port;	/**< Port dla poĹ‚Ä…czeĹ„ bezpoĹ›rednich */
	int version;		/**< Wersja protokoĹ‚u */
	int image_size;		/**< Maksymalny rozmiar obsĹ‚ugiwanych obrazkĂłw w KiB */
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
	int status;		/**< Status dorÄ™czenia */
	int seq;		/**< Numer sekwencyjny wiadomoĹ›ci */
};

/**
 * Opis zdarzenia \c GG_EVENT_ACK110.
 */
struct gg_event_ack110 {
	uint8_t msg_type;	/**< Rodzaj wiadomoĹ›ci (0x01 - zwykĹ‚a, 0x02 - konferencja) */
	uint32_t seq;		/**< Numer sekwencyjny */
	uint32_t time;		/**< Czas zdarzenia */
};

/**
 * Opis zdarzenia \c GG_EVENT_USERLIST.
 */
struct gg_event_userlist {
	char type;		/**< Rodzaj odpowiedzi */
	char *reply;		/**< TreĹ›Ä‡ odpowiedzi */
};

/**
 * Opis zdarzenia \c GG_EVENT_DCC_VOICE_DATA.
 */
struct gg_event_dcc_voice_data {
	uint8_t *data;		/**< Dane dĹşwiÄ™kowe */
	int length;		/**< Rozmiar danych dĹşwiÄ™kowych */
};

/**
 * Opis zdarzenia \c GG_EVENT_IMAGE_REQUEST.
 */
struct gg_event_image_request {
	uin_t sender;		/**< Nadawca ĹĽÄ…dania */
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
	struct gg_dcc7 *dcc7;	/**< Struktura poĹ‚Ä…czenia */
};

/**
 * Opis zdarzenia \c GG_EVENT_DCC7_PENDING.
 */
struct gg_event_dcc7_pending {
	struct gg_dcc7 *dcc7;	/**< Struktura poĹ‚Ä…czenia */
};

/**
 * Opis zdarzenia \c GG_EVENT_DCC7_REJECT.
 */
struct gg_event_dcc7_reject {
	struct gg_dcc7 *dcc7;	/**< Struktura poĹ‚Ä…czenia */
	int reason;		/**< powĂłd odrzucenia */
};

/**
 * Opis zdarzenia \c GG_EVENT_DCC7_ACCEPT.
 */
struct gg_event_dcc7_accept {
	struct gg_dcc7 *dcc7;	/**< Struktura poĹ‚Ä…czenia */
	int type;		/**< SposĂłb poĹ‚Ä…czenia (P2P, przez serwer) */
	uint32_t remote_ip;	/**< Adres zdalnego klienta */
	uint16_t remote_port;	/**< Port zdalnego klienta */
};

/**
 * Opis zdarzenia \c GG_EVENT_DCC7_DONE.
 */
struct gg_event_dcc7_done {
	struct gg_dcc7 *dcc7;	/**< Struktura poĹ‚Ä…czenia */
};

/**
 * Opis zdarzenia \c GG_EVENT_TYPING_NOTIFICATION.
 */
struct gg_event_typing_notification {
	uin_t uin;		/**< Numer rozmĂłwcy */
	int length;		/**< DĹ‚ugoĹ›Ä‡ tekstu */
};

/**
 * Atrybut uĹĽytkownika.
 */
struct gg_event_user_data_attr {
	int type;		/**< Typ atrybutu */
	char *key;		/**< Klucz */
	char *value;		/**< WartoĹ›Ä‡ */
};

/**
 * Struktura opisujÄ…ca kontakt w zdarzeniu GG_EVENT_USER_DATA.
 */
struct gg_event_user_data_user {
	uin_t uin;		/**< Numer kontaktu */
	size_t attr_count;	/**< Liczba atrybutĂłw */
	struct gg_event_user_data_attr *attrs;	/**< Lista atrybutĂłw */
};

/**
 * Opis zdarzenia \c GG_EVENT_USER_DATA.
 */
struct gg_event_user_data {
	int type;		/**< Rodzaj informacji o kontaktach */
	size_t user_count;	/**< Liczba kontaktĂłw */
	struct gg_event_user_data_user *users;	/**< Lista kontaktĂłw */
};

/**
 * Struktura opisujÄ…ca sesjÄ™ multilogowania.
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
	uint32_t version;		/**< Numer wersji listy kontaktĂłw na serwerze */
};

/**
 * Opis zdarzenia \c GG_EVENT_USERLIST100_REPLY.
 */
struct gg_event_userlist100_reply {
	char type;			/**< Rodzaj odpowiedzi */
	uint32_t version;		/**< Aktualna wersja listy kontaktĂłw na serwerze */
	char format_type;		/**< Typ formatu listy kontaktĂłw (ĹĽÄ…dany w \c gg_userlist100_request.format_type) */
	char *reply;			/**< TreĹ›Ä‡ listy kontaktĂłw w przesyĹ‚anej wersji i formacie */
};

/**
 * Opis zdarzenia \c GG_EVENT_IMTOKEN.
 */
struct gg_event_imtoken {
	char *imtoken;			/**< WartoĹ›Ä‡ IMTOKEN */
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
	uint32_t participants_count;	/**< IloĹ›Ä‡ uczestnikĂłw */
	uin_t *participants;		/**< Lista uczestnikĂłw */
};

/**
 * Opis zdarzenia \c GG_EVENT_CHAT_INFO_UPDATE.
 */
struct gg_event_chat_info_update {
	uint64_t id;			/**< Identyfikator konferencji */
	uint32_t type;			/**< Typ aktualizacji (\c GG_CHAT_INFO_UPDATE_*) */
	uin_t participant;		/**< Uczestnik, ktĂłrego dotyczy aktualizacja */
	uin_t inviter;			/**< Uczestnik inicjujÄ…cy aktualizacjÄ™ (zapraszajÄ…cy) */
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
 * Unia wszystkich zdarzeĹ„ zwracanych przez funkcje \c gg_watch_fd(), 
 * \c gg_dcc_watch_fd() i \c gg_dcc7_watch_fd().
 *
 * \ingroup events
 */
union gg_event_union {
	enum gg_failure_t failure;	/**< BĹ‚Ä…d poĹ‚Ä…czenia (\c GG_EVENT_CONN_FAILED) */
	struct gg_notify_reply *notify;	/**< Zmiana statusu kontaktĂłw (\c GG_EVENT_NOTIFY) */
	struct gg_event_notify_descr notify_descr;	/**< Zmiana statusu kontaktĂłw (\c GG_EVENT_NOTIFY_DESCR) */
	struct gg_event_status status;	/**< Zmiana statusu kontaktĂłw (\c GG_EVENT_STATUS) */
	struct gg_event_status60 status60;	/**< Zmiana statusu kontaktĂłw (\c GG_EVENT_STATUS60) */
	struct gg_event_notify60 *notify60;	/**< Zmiana statusu kontaktĂłw (\c GG_EVENT_NOTIFY60) */
	struct gg_event_msg msg;	/**< Otrzymano wiadomoĹ›Ä‡ (\c GG_EVENT_MSG) */
	struct gg_event_ack ack;	/**< Potwierdzenie wiadomoĹ›ci (\c GG_EVENT_ACK) */
	struct gg_event_ack110 ack110;	/**< Potwierdzenie wysĹ‚ania wiadomoĹ›ci (11.0) (\c GG_EVENT_ACK110) */
	struct gg_event_image_request image_request;	/**< Ĺ»Ä…danie wysĹ‚ania obrazka (\c GG_EVENT_IMAGE_REQUEST) */
	struct gg_event_image_reply image_reply;	/**< OdpowiedĹş z obrazkiem (\c GG_EVENT_IMAGE_REPLY) */
	struct gg_event_userlist userlist;	/**< OdpowiedĹş listy kontaktĂłw (\c GG_EVENT_USERLIST) */
	gg_pubdir50_t pubdir50;	/**< OdpowiedĹş katalogu publicznego (\c GG_EVENT_PUBDIR50_*) */
	struct gg_event_xml_event xml_event;	/**< Zdarzenie systemowe (\c GG_EVENT_XML_EVENT) */
	struct gg_event_json_event json_event;	/**< Zdarzenie systemowe (\c GG_EVENT_JSON_EVENT) */
	struct gg_dcc *dcc_new;	/**< Nowe poĹ‚Ä…czenie bezpoĹ›rednie (\c GG_EVENT_DCC_NEW) */
	enum gg_error_t dcc_error;	/**< BĹ‚Ä…d poĹ‚Ä…czenia bezpoĹ›redniego (\c GG_EVENT_DCC_ERROR) */
	struct gg_event_dcc_voice_data dcc_voice_data;	/**< Dane poĹ‚Ä…czenia gĹ‚osowego (\c GG_EVENT_DCC_VOICE_DATA) */
	struct gg_dcc7 *dcc7_new;	/**< Nowe poĹ‚Ä…czenie bezpoĹ›rednie (\c GG_EVENT_DCC7_NEW) */
	enum gg_error_t dcc7_error;	/**< BĹ‚Ä…d poĹ‚Ä…czenia bezpoĹ›redniego (\c GG_EVENT_DCC7_ERROR) */
	struct gg_event_dcc7_connected dcc7_connected;	/**< Informacja o zestawieniu poĹ‚Ä…czenia bezpoĹ›redniego (\c GG_EVENT_DCC7_CONNECTED) */
	struct gg_event_dcc7_pending dcc7_pending;	/**< Trwa prĂłba poĹ‚Ä…czenia bezpoĹ›redniego (\c GG_EVENT_DCC7_PENDING) */
	struct gg_event_dcc7_reject dcc7_reject;	/**< Odrzucono poĹ‚Ä…czenia bezpoĹ›redniego (\c GG_EVENT_DCC7_REJECT) */
	struct gg_event_dcc7_accept dcc7_accept;	/**< Zaakceptowano poĹ‚Ä…czenie bezpoĹ›rednie (\c GG_EVENT_DCC7_ACCEPT) */
	struct gg_event_dcc7_done dcc7_done;	/**< ZakoĹ„czono poĹ‚Ä…czenie bezpoĹ›rednie (\c GG_EVENT_DCC7_DONE) */
	struct gg_event_typing_notification typing_notification;	/**< Powiadomienie o pisaniu */
	struct gg_event_user_data user_data;	/**< Informacje o kontaktach */
	struct gg_event_msg multilogon_msg;	/**< Inna sesja wysĹ‚aĹ‚a wiadomoĹ›Ä‡ (\c GG_EVENT_MULTILOGON_MSG) */
	struct gg_event_multilogon_info multilogon_info;	/**< Informacja o innych sesjach multilogowania (\c GG_EVENT_MULTILOGON_INFO) */
	struct gg_event_userlist100_version userlist100_version;	/**< Informacja o numerze wersji listy kontaktĂłw na serwerze (\c GG_EVENT_USERLIST100_VERSION) */
	struct gg_event_userlist100_reply userlist100_reply;	/**< OdpowiedĹş listy kontaktĂłw (10.0) (\c GG_EVENT_USERLIST100_REPLY) */
	struct gg_event_imtoken imtoken;	/**< CiÄ…g IMTOKEN (11.0) (\c GG_EVENT_IMTOKEN) */
	struct gg_event_pong110 pong110;	/**< Utrzymanie poĹ‚Ä…czenia (11.0) (\c GG_EVENT_PONG110) */
	struct gg_event_chat_info chat_info;	/**< Informacje o konferencji (11.0) (\c GG_EVENT_CHAT_INFO) */
	struct gg_event_chat_info_update chat_info_update;	/**< Aktualizacja informacji o konferencji (11.0) (\c GG_EVENT_CHAT_INFO_UPDATE) */
	struct gg_event_chat_created chat_created;	/**< Potwierdzenie utworzenia konferencji (11.0) (\c GG_EVENT_CHAT_CREATED) */
	struct gg_event_chat_invite_ack chat_invite_ack;	/**< Potwierdzenie wysĹ‚ania zaproszenia do konferencji (11.0) (\c GG_EVENT_CHAT_INVITE_ACK) */
};

/**
 * Opis zdarzenia.
 *
 * Zwracany przez funkcje \c gg_watch_fd(), \c gg_dcc_watch_fd()
 * i \c gg_dcc7_watch_fd(). Po przeanalizowaniu naleĹĽy zwolniÄ‡
 * za pomocÄ… \c gg_event_free().
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
	GG_PUBDIR50_FIRSTNAME,	/**< ImiÄ™ */
	GG_PUBDIR50_LASTNAME,	/**< Nazwisko */
	GG_PUBDIR50_NICKNAME,	/**< Pseudonim */
	GG_PUBDIR50_BIRTHYEAR,	/**< Rok urodzenia lub przedziaĹ‚ lat oddzielony spacjÄ… */
	GG_PUBDIR50_CITY,	/**< MiejscowoĹ›Ä‡ */
	GG_PUBDIR50_GENDER,	/**< PĹ‚eÄ‡ */
	GG_PUBDIR50_ACTIVE,	/**< Osoba dostÄ™pna (tylko wyszukiwanie) */
	GG_PUBDIR50_START,	/**< Numer poczÄ…tkowy wyszukiwania (tylko wyszukiwanie) */
	GG_PUBDIR50_FAMILYNAME,	/**< Nazwisko rodowe (tylko wysyĹ‚anie informacji o sobie) */
	GG_PUBDIR50_FAMILYCITY,	/**< MiejscowoĹ›Ä‡ pochodzenia (tylko wysyĹ‚anie informacji o sobie) */
};

/**
 * \ingroup pubdir50
 *
 * WartoĹ›Ä‡ pola GG_PUBDIR50_GENDER przy wyszukiwaniu. Brak pola oznacza dowolnÄ… pĹ‚eÄ‡.
 */
enum {
	GG_PUBDIR50_GENDER_FEMALE,	/**< Kobieta */
	GG_PUBDIR50_GENDER_MALE,	/**< MÄ™ĹĽczyzna */
};

/**
 * \ingroup pubdir50
 *
 * WartoĹ›Ä‡ pola GG_PUBDIR50_GENDER przy wysyĹ‚aniu informacji o sobie.
 */
enum {
	GG_PUBDIR50_GENDER_SET_FEMALE,	/**< Kobieta */
	GG_PUBDIR50_GENDER_SET_MALE,	/**< MÄ™ĹĽczyzna */
};

/**
 * \ingroup pubdir50
 *
 * WartoĹ›Ä‡ pola GG_PUBDIR50_ACTIVE.
 */
enum {
	GG_PUBDIR50_ACTIVE_TRUE,	/**< Wyszukaj tylko osoby dostÄ™pne */
};

#endif	/* DOXYGEN */

/**
 * PowĂłd bĹ‚Ä™du operacji na katalogu publicznym.
 *
 * \ingroup http
 */
typedef enum {
	GG_PUBDIR_ERROR_NONE = 0,	/**< Brak bĹ‚Ä™du */
	GG_PUBDIR_ERROR_OTHER,	/**< Nieznany bĹ‚Ä…d */
	GG_PUBDIR_ERROR_TOKEN,	/**< BĹ‚Ä™dny token */
	GG_PUBDIR_ERROR_OLD_PASSWORD,	/**< Niepoprawne stare hasĹ‚o */
	GG_PUBDIR_ERROR_NEW_PASSWORD,	/**< Niepoprawne nowe hasĹ‚o */
} gg_pubdir_error_t;

/**
 * Wynik operacji na katalogu publicznym.
 *
 * \ingroup http
 */
struct gg_pubdir {
	int success;		/**< Flaga powodzenia operacji */
	uin_t uin;		/**< Otrzymany numer lub 0 w przypadku bĹ‚Ä™du */
	gg_pubdir_error_t error;	/**< PowĂłd bĹ‚Ä™du */
};

int gg_pubdir_watch_fd(struct gg_http *f);
void gg_pubdir_free(struct gg_http *f);

/**
 * Token autoryzacji niektĂłrych operacji HTTP.
 * 
 * \ingroup token
 */
struct gg_token {
	int width;		/**< SzerokoĹ›Ä‡ obrazka */
	int height;		/**< WysokoĹ›Ä‡ obrazka */
	int length;		/**< Liczba znakĂłw w tokenie */
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

#define GG_DCC_VOICE_FRAME_LENGTH 195		/**< Rozmiar pakietu gĹ‚osowego przed wersjÄ… Gadu-Gadu 5.0.5 */
#define GG_DCC_VOICE_FRAME_LENGTH_505 326	/**< Rozmiar pakietu gĹ‚osowego od wersji Gadu-Gadu 5.0.5 */

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
#define GG_DEBUG_NET 1		/**< Rejestracja zdarzeĹ„ zwiÄ…zanych z sieciÄ… */
#define GG_DEBUG_TRAFFIC 2	/**< Rejestracja ruchu sieciowego */
#define GG_DEBUG_DUMP 4		/**< Rejestracja zawartoĹ›ci pakietĂłw */
#define GG_DEBUG_FUNCTION 8	/**< Rejestracja wywoĹ‚aĹ„ funkcji */
#define GG_DEBUG_MISC 16	/**< Rejestracja rĂłĹĽnych informacji */
#define GG_DEBUG_VERBOSE 32	/**< Rejestracja informacji szczegĂłĹ‚owych */
#define GG_DEBUG_WARNING 64	/**< Rejestracja ostrzeĹĽeĹ„ */
#define GG_DEBUG_ERROR 128	/**< Rejestracja bĹ‚Ä™dĂłw krytycznych */
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
 * Lista funkcji biblioteki, ktĂłre zaleĹĽÄ… od zewnÄ™trznych bibliotek.
 *
 * \ingroup version
 */
typedef enum {
	GG_LIBGADU_FEATURE_SSL,		/**< Biblioteka obsĹ‚uguje poĹ‚Ä…czenia szyfrowane */
	GG_LIBGADU_FEATURE_PTHREAD,	/**< Biblioteka obsĹ‚uguje rozwiÄ…zywanie nazw za pomocÄ… wÄ…tkĂłw */
	GG_LIBGADU_FEATURE_USERLIST100,	/**< Biblioteka obsĹ‚uguje listÄ™ kontaktĂłw zgodnÄ… z Gadu-Gadu 10 */
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
	GG_PUBDIR50_WRITE,	/**< WysĹ‚anie do serwera informacji o sobie */
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
 * Kolejka odbieranych obrazkĂłw.
 */
struct gg_image_queue {
	uin_t sender;			/**< Nadawca obrazka */
	uint32_t size;			/**< Rozmiar obrazka */
	uint32_t crc32;			/**< Suma kontrolna CRC32 */
	char *filename;			/**< Nazwa pliku */
	char *image;			/**< Bufor z odebranymi danymi */
	uint32_t done;			/**< Rozmiar odebranych danych */

	struct gg_image_queue *next;	/**< Kolejny element listy */

	uint32_t packet_type;		/**< \brief Rodzaj odbieranych pakietĂłw. W niektĂłrych przypadkach (przy multilogowaniu) serwer wysyĹ‚a nam dwie kopie obrazka jako dwa rĂłĹĽne typy pakietĂłw */
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

/* PoniĹĽsze makra zostaĹ‚y zachowane dla zgodnoĹ›ci API */
#define GG_FEATURE_MSG80		0
#define GG_FEATURE_STATUS80		0
#define GG_FEATURE_STATUS80BETA		0

#define GG_FEATURE_ALL			(GG_FEATURE_MSG80 | GG_FEATURE_STATUS80 | GG_FEATURE_DND_FFC | GG_FEATURE_IMAGE_DESCR | GG_FEATURE_UNKNOWN_100 | GG_FEATURE_USER_DATA | GG_FEATURE_MSG_ACK | GG_FEATURE_TYPING_NOTIFICATION)

#else

/** 
 * \ingroup login
 *
 * Flagi opcji protokoĹ‚u.
 */
enum {
	GG_FEATURE_MSG77,	/**< Klient ĹĽyczy sobie otrzymywaÄ‡ wiadomoĹ›ci zgodnie z protokoĹ‚em 7.7 */
	GG_FEATURE_STATUS77,	/**< Klient ĹĽyczy sobie otrzymywaÄ‡ zmiany stanu zgodnie z protokoĹ‚em 7.7 */
	GG_FEATURE_DND_FFC,	/**< Klient obsĹ‚uguje statusy "nie przeszkadzaÄ‡" i "poGGadaj ze mnÄ…" */
	GG_FEATURE_IMAGE_DESCR,	/**< Klient obsĹ‚uguje opisy graficzne oraz flagÄ™ \c GG_STATUS80_DESCR_MASK */
};


#endif

#define GG_DEFAULT_DCC_PORT 1550

struct gg_header {
	uint32_t type;			/* typ pakietu */
	uint32_t length;		/* dĹ‚ugoĹ›Ä‡ reszty pakietu */
} GG_PACKED;

#define GG_WELCOME 0x0001
#define GG_NEED_EMAIL 0x0014

struct gg_welcome {
	uint32_t key;			/* klucz szyfrowania hasĹ‚a */
} GG_PACKED;

#define GG_LOGIN 0x000c

struct gg_login {
	uint32_t uin;			/* mĂłj numerek */
	uint32_t hash;			/* hash hasĹ‚a */
	uint32_t status;		/* status na dzieĹ„ dobry */
	uint32_t version;		/* moja wersja klienta */
	uint32_t local_ip;		/* mĂłj adres ip */
	uint16_t local_port;		/* port, na ktĂłrym sĹ‚ucham */
} GG_PACKED;

#define GG_LOGIN_EXT 0x0013

struct gg_login_ext {
	uint32_t uin;			/* mĂłj numerek */
	uint32_t hash;			/* hash hasĹ‚a */
	uint32_t status;		/* status na dzieĹ„ dobry */
	uint32_t version;		/* moja wersja klienta */
	uint32_t local_ip;		/* mĂłj adres ip */
	uint16_t local_port;		/* port, na ktĂłrym sĹ‚ucham */
	uint32_t external_ip;		/* zewnÄ™trzny adres ip */
	uint16_t external_port;		/* zewnÄ™trzny port */
} GG_PACKED;

#define GG_LOGIN60 0x0015

struct gg_login60 {
	uint32_t uin;			/* mĂłj numerek */
	uint32_t hash;			/* hash hasĹ‚a */
	uint32_t status;		/* status na dzieĹ„ dobry */
	uint32_t version;		/* moja wersja klienta */
	uint8_t dunno1;			/* 0x00 */
	uint32_t local_ip;		/* mĂłj adres ip */
	uint16_t local_port;		/* port, na ktĂłrym sĹ‚ucham */
	uint32_t external_ip;		/* zewnÄ™trzny adres ip */
	uint16_t external_port;		/* zewnÄ™trzny port */
	uint8_t image_size;		/* maksymalny rozmiar grafiki w KiB */
	uint8_t dunno2;			/* 0xbe */
} GG_PACKED;

#define GG_LOGIN70 0x0019

struct gg_login70 {
	uint32_t uin;			/* mĂłj numerek */
	uint8_t hash_type;		/* rodzaj hashowania hasĹ‚a */
	uint8_t hash[64];		/* hash hasĹ‚a dopeĹ‚niony zerami */
	uint32_t status;		/* status na dzieĹ„ dobry */
	uint32_t version;		/* moja wersja klienta */
	uint8_t dunno1;			/* 0x00 */
	uint32_t local_ip;		/* mĂłj adres ip */
	uint16_t local_port;		/* port, na ktĂłrym sĹ‚ucham */
	uint32_t external_ip;		/* zewnÄ™trzny adres ip (???) */
	uint16_t external_port;		/* zewnÄ™trzny port (???) */
	uint8_t image_size;		/* maksymalny rozmiar grafiki w KiB */
	uint8_t dunno2;			/* 0xbe */
} GG_PACKED;

#define GG_LOGIN_OK 0x0003

#define GG_LOGIN_FAILED 0x0009

#define GG_PUBDIR50_REQUEST 0x0014

struct gg_pubdir50_request {
	uint8_t type;			/* GG_PUBDIR50_* */
	uint32_t seq;			/* czas wysĹ‚ania zapytania */
} GG_PACKED;

#define GG_PUBDIR50_REPLY 0x000e

struct gg_pubdir50_reply {
	uint8_t type;			/* GG_PUBDIR50_* */
	uint32_t seq;			/* czas wysĹ‚ania zapytania */
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
 * Rodzaje statusĂłw uĹĽytkownika.
 *
 * \ingroup status
 */
enum {
	GG_STATUS_NOT_AVAIL,		/**< NiedostÄ™pny */
	GG_STATUS_NOT_AVAIL_DESCR,	/**< NiedostÄ™pny z opisem */
	GG_STATUS_FFC,			/**< PoGGadaj ze mnÄ… */
	GG_STATUS_FFC_DESCR,		/**< PoGGadaj ze mnÄ… z opisem */
	GG_STATUS_AVAIL,		/**< DostÄ™pny */
	GG_STATUS_AVAIL_DESCR,		/**< DostÄ™pny z opisem */
	GG_STATUS_BUSY,			/**< ZajÄ™ty */
	GG_STATUS_BUSY_DESCR,		/**< ZajÄ™ty z opisem */
	GG_STATUS_DND,			/**< Nie przeszkadzaÄ‡ */
	GG_STATUS_DND_DESCR,		/**< Nie przeszakdzaÄ‡ z opisem */
	GG_STATUS_INVISIBLE,		/**< Niewidoczny (tylko wĹ‚asny status) */
	GG_STATUS_INVISIBLE_DESCR,	/**< Niewidoczny z opisem (tylko wĹ‚asny status) */
	GG_STATUS_BLOCKED,		/**< Zablokowany (tylko status innych) */
	GG_STATUS_GGPLUS,		/**< Status "Korzystam z GG Plus" */
	GG_STATUS_NOT_SET,		/**< Status nie ustawiony (przy logowaniu siÄ™ do sieci) */
	GG_STATUS_IMAGE_MASK,		/**< Flaga bitowa oznaczajÄ…ca opis graficzny (tylko jeĹ›li wybrano \c GG_FEATURE_IMAGE_DESCR) */
	GG_STATUS_DESCR_MASK,		/**< Flaga bitowa oznaczajÄ…ca status z opisem (tylko jeĹ›li wybrano \c GG_FEATURE_IMAGE_DESCR) */
	GG_STATUS_FRIENDS_MASK,		/**< Flaga bitowa dostÄ™pnoĹ›ci tylko dla znajomych */
};

/**
 * Rodzaje statusĂłw uĹĽytkownika. Mapa bitowa.
 *
 * \ingroup status
 */
enum {
	GG_STATUS_FLAG_UNKNOWN,		/**< Przeznaczenie nieznane, ale wystÄ™puje zawsze */
	GG_STATUS_FLAG_VIDEO,		/**< Klient obsĹ‚uguje wideorozmowy */
	GG_STATUS_FLAG_INHERIT,		/**< Synchronizacja statusu do innych klientĂłw (przy logowaniu siÄ™ do sieci) */
	GG_STATUS_FLAG_MOBILE,		/**< Klient mobilny (ikona telefonu komĂłrkowego) */
	GG_STATUS_FLAG_SPAM,		/**< Klient chce otrzymywaÄ‡ linki od nieznajomych */
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
 * Maksymalna dĹ‚ugoĹ›c opisu.
 */
#define GG_STATUS_DESCR_MAXSIZE 255
#define GG_STATUS_DESCR_MAXSIZE_PRE_8_0 70

#define GG_STATUS_MASK 0xff

/* GG_S_F() tryb tylko dla znajomych */
#define GG_S_F(x) (((x) & GG_STATUS_FRIENDS_MASK) != 0)

/* GG_S() stan bez uwzglÄ™dnienia dodatkowych flag */
#define GG_S(x) ((x) & GG_STATUS_MASK)


/* GG_S_FF() chÄ™tny do rozmowy */
#define GG_S_FF(x) (GG_S(x) == GG_STATUS_FFC || GG_S(x) == GG_STATUS_FFC_DESCR)

/* GG_S_AV() dostÄ™pny */
#define GG_S_AV(x) (GG_S(x) == GG_STATUS_AVAIL || GG_S(x) == GG_STATUS_AVAIL_DESCR)

/* GG_S_AW() zaraz wracam */
#define GG_S_AW(x) (GG_S(x) == GG_STATUS_BUSY || GG_S(x) == GG_STATUS_BUSY_DESCR)

/* GG_S_DD() nie przeszkadzaÄ‡ */
#define GG_S_DD(x) (GG_S(x) == GG_STATUS_DND || GG_S(x) == GG_STATUS_DND_DESCR)

/* GG_S_NA() niedostÄ™pny */
#define GG_S_NA(x) (GG_S(x) == GG_STATUS_NOT_AVAIL || GG_S(x) == GG_STATUS_NOT_AVAIL_DESCR)

/* GG_S_I() niewidoczny */
#define GG_S_I(x) (GG_S(x) == GG_STATUS_INVISIBLE || GG_S(x) == GG_STATUS_INVISIBLE_DESCR)


/* GG_S_A() dostÄ™pny lub chÄ™tny do rozmowy */
#define GG_S_A(x) (GG_S_FF(x) || GG_S_AV(x))

/* GG_S_B() zajÄ™ty lub nie przeszkadzaÄ‡ */
#define GG_S_B(x) (GG_S_AW(x) || GG_S_DD(x))


/* GG_S_D() stan opisowy */
#define GG_S_D(x) (GG_S(x) == GG_STATUS_NOT_AVAIL_DESCR || \
		   GG_S(x) == GG_STATUS_FFC_DESCR || \
		   GG_S(x) == GG_STATUS_AVAIL_DESCR || \
		   GG_S(x) == GG_STATUS_BUSY_DESCR || \
		   GG_S(x) == GG_STATUS_DND_DESCR || \
		   GG_S(x) == GG_STATUS_INVISIBLE_DESCR)

/* GG_S_BL() blokowany lub blokujÄ…cy */
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
	uint8_t dunno1;				/* rodzaj wpisu w liĹ›cie */
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
	GG_USER_NORMAL,		/**< ZwykĹ‚y kontakt */
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
	uint16_t remote_port;		/* port, na ktĂłrym sĹ‚ucha klient */
	uint32_t version;		/* wersja klienta */
	uint16_t dunno2;		/* znowu port? */
} GG_PACKED;

#define GG_NOTIFY_REPLY60 0x0011

struct gg_notify_reply60 {
	uint32_t uin;			/* numerek plus flagi w MSB */
	uint8_t status;			/* status danej osoby */
	uint32_t remote_ip;		/* adres ip delikwenta */
	uint16_t remote_port;		/* port, na ktĂłrym sĹ‚ucha klient */
	uint8_t version;		/* wersja klienta */
	uint8_t image_size;		/* maksymalny rozmiar grafiki w KiB */
	uint8_t dunno1;			/* 0x00 */
} GG_PACKED;

#define GG_STATUS60 0x000f

struct gg_status60 {
	uint32_t uin;			/* numerek plus flagi w MSB */
	uint8_t status;			/* status danej osoby */
	uint32_t remote_ip;		/* adres ip delikwenta */
	uint16_t remote_port;		/* port, na ktĂłrym sĹ‚ucha klient */
	uint8_t version;		/* wersja klienta */
	uint8_t image_size;		/* maksymalny rozmiar grafiki w KiB */
	uint8_t dunno1;			/* 0x00 */
} GG_PACKED;

#define GG_NOTIFY_REPLY77 0x0018

struct gg_notify_reply77 {
	uint32_t uin;			/* numerek plus flagi w MSB */
	uint8_t status;			/* status danej osoby */
	uint32_t remote_ip;		/* adres ip delikwenta */
	uint16_t remote_port;		/* port, na ktĂłrym sĹ‚ucha klient */
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
	uint16_t remote_port;		/* port, na ktĂłrym sĹ‚ucha klient */
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
#define GG_CLASS_EXT GG_CLASS_ACK	/**< Dla kompatybilnoĹ›ci wstecz */

#else

/**
 * Klasy wiadomoĹ›ci. WartoĹ›ci sÄ… maskami bitowymi, ktĂłre w wiÄ™kszoĹ›ci
 * przypadkĂłw moĹĽna Ĺ‚Ä…czyÄ‡ (poĹ‚Ä…czenie \c GG_CLASS_MSG i \c GG_CLASS_CHAT
 * nie ma sensu).
 *
 * \ingroup messages
 */
enum {
	GG_CLASS_MSG,		/**< WiadomoĹ›Ä‡ ma pojawiÄ‡ siÄ™ w osobnym oknie */
	GG_CLASS_CHAT,		/**< WiadomoĹ›Ä‡ ma pojawiÄ‡ siÄ™ w oknie rozmowy */
	GG_CLASS_CTCP,		/**< WiadomoĹ›Ä‡ przeznaczona dla klienta Gadu-Gadu */
	GG_CLASS_ACK,		/**< Klient nie ĹĽyczy sobie potwierdzenia */
	GG_CLASS_QUEUED,	/**< WiadomoĹ›Ä‡ zakolejkowana na serwerze (tylko przy odbieraniu) */
};

#endif	/* DOXYGEN */

/**
 * Maksymalna dĹ‚ugoĹ›Ä‡ wiadomoĹ›ci.
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
 * Struktura opisujÄ…ca formatowanie tekstu. W zaleĹĽnoĹ›ci od wartoĹ›ci pola
 * \c font, zaraz za tÄ… strukturÄ… moĹĽe wystÄ…piÄ‡ \c gg_msg_richtext_color
 * lub \c gg_msg_richtext_image.
 *
 * \ingroup messages
 */
struct gg_msg_richtext_format {
	uint16_t position;	/**< PoczÄ…tkowy znak formatowania (liczony od 0) */
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
 * Atrybuty formatowania wiadomoĹ›ci.
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
 * Struktura opisujÄ…cÄ… kolor tekstu dla atrybutu \c GG_FONT_COLOR.
 *
 * \ingroup messages
 */
struct gg_msg_richtext_color {
	uint8_t red;		/**< SkĹ‚adowa czerwona koloru */
	uint8_t green;		/**< SkĹ‚adowa zielona koloru */
	uint8_t blue;		/**< SkĹ‚adowa niebieska koloru */
} GG_PACKED;

/**
 * Strukturya opisujÄ…ca obrazek wstawiony do wiadomoĹ›ci dla atrubutu
 * \c GG_FONT_IMAGE.
 *
 * \ingroup messages
 */
struct gg_msg_richtext_image {
	uint16_t unknown1;	/**< Nieznane pole o wartoĹ›ci 0x0109 */
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
 * Status dorÄ™czenia wiadomoĹ›ci.
 *
 * \ingroup messages
 */
enum
{
	GG_ACK_DELIVERED,	/**< WiadomoĹ›Ä‡ dostarczono. */
	GG_ACK_QUEUED,		/**< WiadomoĹ›Ä‡ zakolejkowano z powodu niedostÄ™pnoĹ›ci odbiorcy. */
	GG_ACK_BLOCKED,		/**< WiadomoĹ›Ä‡ zablokowana przez serwer (spam, Ĺ›wiÄ…teczne ograniczenia itd.) */
	GG_ACK_MBOXFULL,	/**< WiadomoĹ›ci nie dostarczono z powodu zapeĹ‚nionej kolejki wiadomoĹ›ci odbiorcy. */
	GG_ACK_NOT_DELIVERED	/**< WiadomoĹ›ci nie dostarczono (tylko dla \c GG_CLASS_CTCP). */
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
	GG_USERLIST_PUT,	/**< Eksport listy kontaktĂłw. */
	GG_USERLIST_GET,	/**< Import listy kontaktĂłw. */
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
	GG_USERLIST_PUT_REPLY,	/**< Wyeksportowano listy kontaktĂłw. */
	GG_USERLIST_GET_REPLY,	/**< Zaimportowano listÄ™ kontaktĂłw. */
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
	GG_USERLIST100_PUT,	/**< Eksport listy kontaktĂłw. */
	GG_USERLIST100_GET,	/**< Import listy kontaktĂłw. */
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
 * Typ formatu listy kontaktĂłw (10.0).
 */
enum {
	GG_USERLIST100_FORMAT_TYPE_NONE,	/**< Brak treĹ›ci listy kontaktĂłw. */
	GG_USERLIST100_FORMAT_TYPE_GG70,	/**< Format listy kontaktĂłw zgodny z Gadu-Gadu 7.0. */
	GG_USERLIST100_FORMAT_TYPE_GG100,	/**< Format listy kontaktĂłw zgodny z Gadu-Gadu 10.0. */
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
 * Typ odpowiedzi listy kontaktĂłw (10.0).
 */
enum {
	GG_USERLIST100_REPLY_LIST,	/**< W odpowiedzi znajduje siÄ™ aktualna lista kontaktĂłw na serwerze. */
	GG_USERLIST100_REPLY_UPTODATE,	/**< Komunikat o tym, ĹĽe lista kontaktĂłw jest juĹĽ zsynchronizowana. */
	GG_USERLIST100_REPLY_ACK,	/**< Potwierdzenie odebrania nowej wersji listy kontaktĂłw. W polu \c gg_userlist100_reply.version znajduje siÄ™ numer nowej wersji listy kontaktĂłw. */
	GG_USERLIST100_REPLY_REJECT,	/**< Odmowa przyjÄ™cia nowej wersji listy kontaktĂłw. W polu \c gg_userlist100_reply.version znajduje siÄ™ numer wersji listy kontaktĂłw aktualnie przechowywanej przez serwer. */
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
 * pĂłki co, nie znamy dokĹ‚adnie protokoĹ‚u. nie wiemy, co czemu odpowiada.
 * nazwy sÄ… niepowaĹĽne i tymczasowe.
 */
#define GG_DCC_WANT_FILE 0x0003		/* peer chce plik */
#define GG_DCC_HAVE_FILE 0x0001		/* wiÄ™c mu damy */
#define GG_DCC_HAVE_FILEINFO 0x0003	/* niech ma informacje o pliku */
#define GG_DCC_GIMME_FILE 0x0006	/* peer jest pewny */
#define GG_DCC_CATCH_FILE 0x0002	/* wysyĹ‚amy plik */

#define GG_DCC_FILEATTR_READONLY 0x0020

#define GG_DCC_TIMEOUT_SEND 1800	/* 30 minut */
#define GG_DCC_TIMEOUT_GET 1800		/* 30 minut */
#define GG_DCC_TIMEOUT_FILE_ACK 300	/* 5 minut */
#define GG_DCC_TIMEOUT_VOICE_ACK 300	/* 5 minut */

#define GG_DCC7_INFO 0x1f

struct gg_dcc7_info {
	uint32_t uin;			/* numer nadawcy */
	uint32_t type;			/* sposĂłb poĹ‚Ä…czenia */
	gg_dcc7_id_t id;		/* identyfikator poĹ‚Ä…czenia */
	char info[GG_DCC7_INFO_LEN];	/* informacje o poĹ‚Ä…czeniu "ip port" */
	char hash[GG_DCC7_INFO_HASH_LEN];/* skrĂłt "ip" */
} GG_PACKED;

#define GG_DCC7_NEW 0x20

struct gg_dcc7_new {
	gg_dcc7_id_t id;		/* identyfikator poĹ‚Ä…czenia */
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
	uint32_t uin;			/* numer przyjmujÄ…cego poĹ‚Ä…czenie */
	gg_dcc7_id_t id;		/* identyfikator poĹ‚Ä…czenia */
	uint32_t offset;		/* offset przy wznawianiu transmisji */
	uint32_t dunno1;		/* 0x00000000 */
} GG_PACKED;

/* XXX API */
#define GG_DCC7_TYPE_P2P 0x00000001	/**< PoĹ‚Ä…czenie bezpoĹ›rednie */
#define GG_DCC7_TYPE_SERVER 0x00000002	/**< PoĹ‚Ä…czenie przez serwer */

#define GG_DCC7_REJECT 0x22

struct gg_dcc7_reject {
	uint32_t uin;			/**< Numer odrzucajÄ…cego poĹ‚Ä…czenie */
	gg_dcc7_id_t id;		/**< Identyfikator poĹ‚Ä…czenia */
	uint32_t reason;		/**< PowĂłd rozĹ‚Ä…czenia */
} GG_PACKED;

/* XXX API */
#define GG_DCC7_REJECT_BUSY 0x00000001	/**< PoĹ‚Ä…czenie bezpoĹ›rednie juĹĽ trwa, nie umiem obsĹ‚uĹĽyÄ‡ wiÄ™cej */
#define GG_DCC7_REJECT_USER 0x00000002	/**< UĹĽytkownik odrzuciĹ‚ poĹ‚Ä…czenie */
#define GG_DCC7_REJECT_VERSION 0x00000006	/**< Druga strona ma wersjÄ™ klienta nieobsĹ‚ugujÄ…cÄ… poĹ‚Ä…czeĹ„ bezpoĹ›rednich tego typu */

#define GG_DCC7_ID_REQUEST 0x23

struct gg_dcc7_id_request {
	uint32_t type;			/**< Rodzaj tranmisji */
} GG_PACKED;

/* XXX API */
#define GG_DCC7_TYPE_VOICE 0x00000001	/**< Transmisja gĹ‚osu */
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
