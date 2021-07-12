/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_defaultbg[]   = "#121212";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_defaultbg, col_gray2 },
    [SchemeSel]  = { col_gray4, col_gray1, col_cyan },
};


typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *minist[] = {"st", "-n", "spminiterm", "-f", "mono:pixelsize=16:antialias=true:autohint=true:style=Regular", "-g", "110x26", NULL };
const char *vifm[] = {"st", "-n", "spvifm", "-f", "mono:pixelsize=16:antialias=true:autohint=true:style=Regular", "-g", "92x42", "-e", "vifm", NULL };
const char *keepxc[] = {"keepassxc", NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"spminiterm", minist},
	{"spvifm",     vifm},
	{"keepassxc",  keepxc},
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance      title       tags mask       isfloating   monitor */
	{ "Gimp",     NULL,         NULL,       0,              1,           -1 },
	{ "Firefox",  NULL,         NULL,       1 << 8,         0,           -1 },
	{ NULL,		  "spminiterm",	NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spvifm",		NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "caloteiro",	NULL,		0,		        1,			 -1 },
	{ NULL,		  "keepassxc",	NULL,		SPTAG(2),		1,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
/*	{ "><>",      NULL },     no layout function means floating behavior */
/*	{ "[M]",      monocle }, */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *dmenucmdcalc[] = { "dmenu_run", "--font", "mono:pixelsize=14:antialias=true:autohint=true:style=Regular", "-m", dmenumon, "-=", NULL };
static const char *termcmd[]  = { "st", "-f", "mono:pixelsize=20:antialias=true:autohint=true:style=Regular",  NULL };
static const char *newsboat[] = { "st", "-f", "mono:pixelsize=20:antialias=true:autohint=true:style=Regular", "-e", "/usr/bin/sh", "-c", "newsboat", NULL };
static const char *clipmenu[] = { "clipmenu", NULL };
static const char *slock[] = { "slock", NULL };
static const char *passmenu[] = { "passmenu", NULL };

static Key keys[] = {
	/* modifier                     key        function         argument */
	{ MODKEY,                       XK_d,      spawn,           {.v = dmenucmd } },
	{ MODKEY,                       XK_a,      spawn,           {.v = dmenucmdcalc } },
	{ MODKEY,                       XK_comma,  spawn,           {.v = slock } },
	{ MODKEY,                       XK_Return, spawn,           {.v = termcmd } },
    { MODKEY,                       XK_s,      togglescratch,   {.ui = 0 } },
    { MODKEY,                       XK_e,      togglescratch,   {.ui = 1 } },
    { MODKEY,                       XK_r,      togglescratch,   {.ui = 2 } },
    { MODKEY,                       XK_n,      spawn,           {.v = newsboat } },
    { MODKEY,                       XK_g,      spawn,           {.v = clipmenu } },
    { MODKEY,                       XK_p,      spawn,           {.v = passmenu } },
	{ MODKEY,                       XK_b,      togglebar,       {0} },
	{ MODKEY,                       XK_j,      focusstack,      {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,      {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_i,      incnmaster,      {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,        {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,        {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return, zoom,            {0} },
	{ MODKEY,                       XK_Tab,    view,            {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,      {0} },
    { MODKEY,                       XK_f,      togglefullscr,   {0} },
    { MODKEY,                       XK_q,      killclient,      {0} },
    { MODKEY|ShiftMask,             XK_q,      killclient,      {0} },
  /*{ MODKEY,                       XK_t,      setlayout,       {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,       {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,       {.v = &layouts[2]} }, */
	{ MODKEY,                       XK_space,  setlayout,       {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,  {0} },
	{ MODKEY,                       XK_0,      view,            {.ui = ~0 } },
	/* { MODKEY|ShiftMask,             XK_0,      tag,             {.ui = ~0 } }, */
	/* { MODKEY,                       XK_comma,  focusmon,        {.i = -1 } }, */
	/* { MODKEY,                       XK_period, focusmon,        {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_comma,  tagmon,          {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period, tagmon,          {.i = +1 } }, */
	TAGKEYS(                        XK_1,                       0)
	TAGKEYS(                        XK_2,                       1)
	TAGKEYS(                        XK_3,                       2)
	TAGKEYS(                        XK_4,                       3)
	TAGKEYS(                        XK_5,                       4)
	TAGKEYS(                        XK_6,                       5)
    { MODKEY|ShiftMask,             XK_Escape, quit,            {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
  /*{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },*/
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

