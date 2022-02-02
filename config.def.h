/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int enablegaps         = 1;
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int attachmode         = 2;        /* 0 master (default), 1 = above, 2 = aside, 3 = below, 4 = bottom */
static const int focusedontop       = 1;        /* 1 means focused client is shown on top of floating windows */
static int floatposgrid_x           = 5;        /* float grid columns */
static int floatposgrid_y           = 5;        /* float grid rows */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
  /*               fg           bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

#define WTYPE "_NET_WM_WINDOW_TYPE_"
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.role = "pop-up", .isfloating = 1)
  RULE(.class = "Firefox", .tags = 1 << 8)
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "D[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

static const MonitorRule monrules[] = {
	/* monitor  tag  layout  mfact  nmaster  showbar  topbar */
	{  1,       -1,  5,      -1,    -1,      -1,      -1     }, // use a different layout for the second monitor
	{  -1,      -1,  0,      -1,    -1,      -1,      -1     }, // default
};

/* key definitions */
#define M Mod4Mask
#define A Mod1Mask
#define R Mod3Mask
#define S ShiftMask
#define C ControlMask
#define TAGKEYS(KEY,TAG) \
	{ M,     KEY,   view,           {.ui = 1 << TAG} }, \
	{ M|C,   KEY,   toggleview,     {.ui = 1 << TAG} }, \
	{ M|S,   KEY,   tag,            {.ui = 1 << TAG} }, \
	{ M|C|S, KEY,   toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier   key        function        argument */
	{ M,          XK_p,      spawn,          {.v = dmenucmd } },
	{ M|S,        XK_Return, spawn,          {.v = termcmd } },
	{ M,          XK_b,      togglebar,      {0} },
	{ M,          XK_j,      focusstack,     {.i = +1 } },
	{ M,          XK_k,      focusstack,     {.i = -1 } },
	{ M,          XK_i,      incnmaster,     {.i = +1 } },
	{ M,          XK_d,      incnmaster,     {.i = -1 } },
	{ M,          XK_h,      setmfact,       {.f = -0.05} },
	{ M,          XK_l,      setmfact,       {.f = +0.05} },
	{ M|S,        XK_h,      setcfact,       {.f = +0.25} },
	{ M|S,        XK_l,      setcfact,       {.f = -0.25} },
	{ M|S,        XK_o,      setcfact,       {.f =  0.00} },
	{ M|A,        XK_u,      incrgaps,       {.i = +1 } },
	{ M|A|S,      XK_u,      incrgaps,       {.i = -1 } },
	{ M|A,        XK_i,      incrigaps,      {.i = +1 } },
	{ M|A|S,      XK_i,      incrigaps,      {.i = -1 } },
	{ M|A,        XK_o,      incrogaps,      {.i = +1 } },
	{ M|A|S,      XK_o,      incrogaps,      {.i = -1 } },
	{ M|A,        XK_6,      incrihgaps,     {.i = +1 } },
	{ M|A|S,      XK_6,      incrihgaps,     {.i = -1 } },
	{ M|A,        XK_7,      incrivgaps,     {.i = +1 } },
	{ M|A|S,      XK_7,      incrivgaps,     {.i = -1 } },
	{ M|A,        XK_8,      incrohgaps,     {.i = +1 } },
	{ M|A|S,      XK_8,      incrohgaps,     {.i = -1 } },
	{ M|A,        XK_9,      incrovgaps,     {.i = +1 } },
	{ M|A|S,      XK_9,      incrovgaps,     {.i = -1 } },
	{ M|A,        XK_0,      togglegaps,     {0} },
	{ M|A|S,      XK_0,      defaultgaps,    {0} },
	{ M,          XK_Return, zoom,           {0} },
	{ M,          XK_Tab,    view,           {0} },
	{ M|S,        XK_c,      killclient,     {0} },
	{ M,          XK_t,      setlayout,      {.v = &layouts[0]} },
	{ M,          XK_f,      setlayout,      {.v = &layouts[1]} },
	{ M,          XK_m,      setlayout,      {.v = &layouts[2]} },
	{ M,          XK_space,  setlayout,      {0} },
	{ M|S,        XK_space,  togglefloating, {0} },
	{ M,          XK_0,      view,           {.ui = ~0 } },
	{ M|S,        XK_0,      tag,            {.ui = ~0 } },
	{ M,          XK_comma,  focusmon,       {.i = -1 } },
	{ M,          XK_period, focusmon,       {.i = +1 } },
	{ M|S,        XK_comma,  tagmon,         {.i = -1 } },
	{ M|S,        XK_period, tagmon,         {.i = +1 } },
	/* Client position is limited to monitor window area */
	{ R,          XK_u,      floatpos,       {.v = "-26x -26y" } }, // ↖
	{ R,          XK_i,      floatpos,       {.v = "  0x -26y" } }, // ↑
	{ R,          XK_o,      floatpos,       {.v = " 26x -26y" } }, // ↗
	{ R,          XK_j,      floatpos,       {.v = "-26x   0y" } }, // ←
	{ R,          XK_l,      floatpos,       {.v = " 26x   0y" } }, // →
	{ R,          XK_m,      floatpos,       {.v = "-26x  26y" } }, // ↙
	{ R,          XK_comma,  floatpos,       {.v = "  0x  26y" } }, // ↓
	{ R,          XK_period, floatpos,       {.v = " 26x  26y" } }, // ↘
	/* Absolute positioning (allows moving windows between monitors) */
	{ R|C,        XK_u,      floatpos,       {.v = "-26a -26a" } }, // ↖
	{ R|C,        XK_i,      floatpos,       {.v = "  0a -26a" } }, // ↑
	{ R|C,        XK_o,      floatpos,       {.v = " 26a -26a" } }, // ↗
	{ R|C,        XK_j,      floatpos,       {.v = "-26a   0a" } }, // ←
	{ R|C,        XK_l,      floatpos,       {.v = " 26a   0a" } }, // →
	{ R|C,        XK_m,      floatpos,       {.v = "-26a  26a" } }, // ↙
	{ R|C,        XK_comma,  floatpos,       {.v = "  0a  26a" } }, // ↓
	{ R|C,        XK_period, floatpos,       {.v = " 26a  26a" } }, // ↘
	/* Resize client, client center position is fixed which means that client expands in all directions */
	{ R|S,        XK_u,      floatpos,       {.v = "-26w -26h" } }, // ↖
	{ R|S,        XK_i,      floatpos,       {.v = "  0w -26h" } }, // ↑
	{ R|S,        XK_o,      floatpos,       {.v = " 26w -26h" } }, // ↗
	{ R|S,        XK_j,      floatpos,       {.v = "-26w   0h" } }, // ←
	{ R|S,        XK_k,      floatpos,       {.v = "800W 800H" } }, // ·
	{ R|S,        XK_l,      floatpos,       {.v = " 26w   0h" } }, // →
	{ R|S,        XK_m,      floatpos,       {.v = "-26w  26h" } }, // ↙
	{ R|S,        XK_comma,  floatpos,       {.v = "  0w  26h" } }, // ↓
	{ R|S,        XK_period, floatpos,       {.v = " 26w  26h" } }, // ↘
	/* Client is positioned in a floating grid, movement is relative to client's current position */
	{ R|A,        XK_u,      floatpos,       {.v = "-1p -1p" } }, // ↖
	{ R|A,        XK_i,      floatpos,       {.v = " 0p -1p" } }, // ↑
	{ R|A,        XK_o,      floatpos,       {.v = " 1p -1p" } }, // ↗
	{ R|A,        XK_j,      floatpos,       {.v = "-1p  0p" } }, // ←
	{ R|A,        XK_k,      floatpos,       {.v = " 0p  0p" } }, // ·
	{ R|A,        XK_l,      floatpos,       {.v = " 1p  0p" } }, // →
	{ R|A,        XK_m,      floatpos,       {.v = "-1p  1p" } }, // ↙
	{ R|A,        XK_comma,  floatpos,       {.v = " 0p  1p" } }, // ↓
	{ R|A,        XK_period, floatpos,       {.v = " 1p  1p" } }, // ↘
	TAGKEYS(      XK_1,                      0)
	TAGKEYS(      XK_2,                      1)
	TAGKEYS(      XK_3,                      2)
	TAGKEYS(      XK_4,                      3)
	TAGKEYS(      XK_5,                      4)
	TAGKEYS(      XK_6,                      5)
	TAGKEYS(      XK_7,                      6)
	TAGKEYS(      XK_8,                      7)
	TAGKEYS(      XK_9,                      8)
	{ M,          XK_F5,     xrdb,           {.v = NULL } },
	{ M|S,        XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click            event mask   button      function        argument */
	{ ClkLtSymbol,      0,           Button1,    setlayout,      {0} },
	{ ClkLtSymbol,      0,           Button3,    setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,      0,           Button2,    zoom,           {0} },
	{ ClkStatusText,    0,           Button2,    spawn,          {.v = termcmd } },
	{ ClkClientWin,     M,           Button1,    movemouse,      {0} },
	{ ClkClientWin,     M,           Button2,    togglefloating, {0} },
	{ ClkClientWin,     M,           Button3,    resizemouse,    {0} },
	{ ClkClientWin,     M|S,         Button1,    dragmfact,      {0} },
	{ ClkTagBar,        0,           Button1,    view,           {0} },
	{ ClkTagBar,        0,           Button3,    toggleview,     {0} },
	{ ClkTagBar,        M,           Button1,    tag,            {0} },
	{ ClkTagBar,        M,           Button3,    toggletag,      {0} },
};
