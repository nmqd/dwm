/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int barborder = 0;        /* border pixel of bar */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int enablegaps         = 1;        /* 1 means enable gaps on startup */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int barheight          = 24;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const int horizpadbar        = 10;        /* horizontal padding for statusbar */
static const int vertpadbar         = 10;        /* vertical padding for statusbar */
static const int attachmode         = 2;        /* 0 master (default), 1 = above, 2 = aside, 3 = below, 4 = bottom */
static const int focusedontop       = 0;        /* 1 means focused client is shown on top of floating windows */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int floatposgrid_x           = 5;        /* float grid columns */
static int floatposgrid_y           = 5;        /* float grid rows */
static const char slopspawnstyle[]  = "-t 0 -c 0.92,0.85,0.69,0.3 -o"; /* do NOT define -f (format) here */
static const char slopresizestyle[] = "-t 0 -c 0.92,0.85,0.69,0.3"; /* do NOT define -f (format) here */
static const int riodraw_borders    = 0;        /* 0 or 1, indicates whether the area drawn using slop includes the window borders */
static const int riodraw_matchpid   = 1;        /* 0 or 1, indicates whether to match the PID of the client that was spawned with riospawn */
static const int riodraw_spawnasync = 0;        /* 0 means that the application is only spawned after a successful selection while
                                                 * 1 means that the application is being initialised in the background while the selection is made */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char normfloatcolor[]        = "#005339";
static char selfloatcolor[]         = "#FF2499";
static char normscratchcolor[]      = "#FF8800";
static char selscratchcolor[]       = "#FF0000";
static char *colors[][3] = {
  /*               fg           bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor, selbgcolor, selbordercolor  },
  [SchemeFloatNorm] = { normfgcolor, normbgcolor, normfloatcolor },
  [SchemeFloatSel]  = { selfgcolor, selbgcolor, selfloatcolor  },
	[SchemeScratchNorm] = { normfgcolor, normbgcolor, normscratchcolor },
	[SchemeScratchSel]  = { selfgcolor, selbgcolor, selscratchcolor  },
  [SchemeTags] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeTag1] = { "#9ECE6A", normbgcolor, normbordercolor },
  [SchemeTag2] = { "#E0AF68", normbgcolor, normbordercolor },
  [SchemeTag3] = { "#7DCFFF", normbgcolor, normbordercolor },
  [SchemeTag4] = { "#F7768E", normbgcolor, normbordercolor },
  [SchemeTag5] = { "#BB9AF7", normbgcolor, normbordercolor },
  [SchemeTag6] = { "#414868", normbgcolor, normbordercolor },
  [SchemeTag7] = { "#9ECE6A", normbgcolor, normbordercolor },
  [SchemeTag8] = { "#7AA2F7", normbgcolor, normbordercolor },
  [SchemeTag9] = { "#E0AF68", normbgcolor, normbordercolor },
  [SchemeLayout] = { normfgcolor, normbgcolor, normbordercolor },
};

static char termcol0[] = "#000000"; /* black   */
static char termcol1[] = "#ff0000"; /* red     */
static char termcol2[] = "#33ff00"; /* green   */
static char termcol3[] = "#ff0099"; /* yellow  */
static char termcol4[] = "#0066ff"; /* blue    */
static char termcol5[] = "#cc00ff"; /* magenta */
static char termcol6[] = "#00ffff"; /* cyan    */
static char termcol7[] = "#d0d0d0"; /* white   */
static char termcol8[]  = "#808080"; /* black   */
static char termcol9[]  = "#ff0000"; /* red     */
static char termcol10[] = "#33ff00"; /* green   */
static char termcol11[] = "#ff0099"; /* yellow  */
static char termcol12[] = "#0066ff"; /* blue    */
static char termcol13[] = "#cc00ff"; /* magenta */
static char termcol14[] = "#00ffff"; /* cyan    */
static char termcol15[] = "#ffffff"; /* white   */
static char *termcolor[] = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
};

static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel] = { OPAQUE, baralpha, borderalpha },
  [SchemeFloatNorm] = { OPAQUE, baralpha, borderalpha },
  [SchemeFloatSel] = { OPAQUE, baralpha, borderalpha },
	[SchemeScratchNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeScratchSel] = { OPAQUE, baralpha, borderalpha },
  [SchemeTags] = { OPAQUE, baralpha, borderalpha },
  [SchemeTag1] = { OPAQUE, baralpha, borderalpha },
  [SchemeTag2] = { OPAQUE, baralpha, borderalpha },
  [SchemeTag3] = { OPAQUE, baralpha, borderalpha },
  [SchemeTag4] = { OPAQUE, baralpha, borderalpha },
  [SchemeTag5] = { OPAQUE, baralpha, borderalpha },
  [SchemeTag6] = { OPAQUE, baralpha, borderalpha },
  [SchemeTag7] = { OPAQUE, baralpha, borderalpha },
  [SchemeTag8] = { OPAQUE, baralpha, borderalpha },
  [SchemeTag9] = { OPAQUE, baralpha, borderalpha },
  [SchemeLayout] = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[NUMTAGS] = { NULL };  /* left for compatibility reasons, i.e. code that checks LENGTH(tags) */
static char *tagicons[][NUMTAGS] = {
	[IconsDefault]        = { " ", " ", " ", " ", "漣 ", " ", " ", " ", " " },
	[IconsBullets]        = { "•" },
	[IconsNumbers]        = { "1", "2", "3", "4", "5", "6", "7", "8", "9" },
	[IconsLetters]        = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[IconsText]           = { "terminal", "mail", "music", "files", "prog", "social", "media", "play", "web" },
	[IconsSubscript]      = { " ₁", " ₂", " ₃", " ₄", " ₅", " ₆", " ₇", " ₈", " ₉" },
	[IconsVacant]         = { NULL },
	[IconsOccupied]       = { " ", " ", " ", " ", "漣 ", " ", "磊 ", " ", " " },
	[IconsSelected]       = { NULL },
};

static const int tagschemes[] = {
  SchemeTag1, SchemeTag2, SchemeTag3,
  SchemeTag4, SchemeTag5, SchemeTag6,
  SchemeTag7, SchemeTag8, SchemeTag9,
};

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

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
	RULE(.class = "st-256color", .isterminal = 1)
  RULE(.title = "scratchpad", .floatpos = "50% 50% 60% 60%", .scratchkey = 's')
	RULE(.title = "Event Tester", .noswallow = 1)
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#define PERTAG_VANITYGAPS 1   /* vanitygaps per tag */
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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "st", "-t", "scratchpad", NULL};

static Key keys[] = {
	/* modifier   key        function        argument */
	{ M,          XK_p,      spawn,          {.v = dmenucmd } },
	{ M|S,        XK_Return, spawn,          {.v = termcmd } },
	{ M|C,        XK_Return, riospawn,       {.v = termcmd } },
	{ M,          XK_r,      rioresize,      {0} },
	{ M,          XK_s,      togglescratch,  {.v = scratchpadcmd } },
	{ M|S,        XK_s,      removescratch,  {.v = scratchpadcmd } },
	{ M|C,        XK_s,      setscratch,     {.v = scratchpadcmd } },
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
	{ M|C,        XK_Tab,       shiftview,   { .i = +1 } },
	{ M|C,        XK_backslash, shiftview,   { .i = -1 } },
	{ M|S,        XK_Tab,       shiftviewclients, { .i = +1 } },
	{ M|S,        XK_backslash, shiftviewclients, { .i = -1 } },
	{ M|S,        XK_c,      killclient,     {0} },
	{ M,          XK_t,      setlayout,      {.v = &layouts[0]} },
	{ M|S,        XK_t,      setlayout,      {.v = &layouts[2]} },
	{ M,          XK_y,      setlayout,      {.v = &layouts[5]} },
	{ M|S,        XK_y,      setlayout,      {.v = &layouts[6]} },
	{ M,          XK_m,      setlayout,      {.v = &layouts[1]} },
	{ M|S,        XK_m,      setlayout,      {.v = &layouts[4]} },
	{ M,          XK_g,      setlayout,      {.v = &layouts[7]} },
	{ M|S,        XK_g,      setlayout,      {.v = &layouts[11]} },
	{ M,          XK_e,      setlayout,      {.v = &layouts[13]} },
	{ M,          XK_space,  setlayout,      {0} },
	{ M|S,        XK_space,  togglefloating, {0} },
	{ M,          XK_0,      view,           {.ui = ~0 } },
	{ M|S,        XK_0,      tag,            {.ui = ~0 } },
	{ M,          XK_comma,  focusmon,       {.i = -1 } },
	{ M,          XK_period, focusmon,       {.i = +1 } },
	{ M|S,        XK_comma,  tagmon,         {.i = -1 } },
	{ M|S,        XK_period, tagmon,         {.i = +1 } },
	{ M|C,        XK_comma,  cyclelayout,    {.i = -1 } },
	{ M|C,        XK_period, cyclelayout,    {.i = +1 } },
	// { M|S,        XK_a,      seticonset,     {.i = 0 } },
	// { M|S,        XK_b,      seticonset,     {.i = 1 } },
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
	{ ClkStatusText,    0,           Button1,    sigstatusbar,   {.i = 1} },
	{ ClkStatusText,    0,           Button2,    sigstatusbar,   {.i = 2} },
	{ ClkStatusText,    0,           Button3,    sigstatusbar,   {.i = 3} },
	{ ClkStatusText,    0,           Button4,    sigstatusbar,   {.i = 4} },
	{ ClkStatusText,    0,           Button5,    sigstatusbar,   {.i = 5} },
	{ ClkStatusText,    S,           Button1,    sigstatusbar,   {.i = 6} },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,     M,           Button1,    moveorplace,    {.i = 1} },
	{ ClkClientWin,     M,           Button2,    togglefloating, {0} },
	{ ClkClientWin,     M,           Button3,    resizemouse,    {0} },
	{ ClkClientWin,     M|S,         Button1,    dragmfact,      {0} },
	{ ClkClientWin,     M|S,         Button3,    dragcfact,      {0} },
	{ ClkTagBar,        0,           Button1,    view,           {0} },
	{ ClkTagBar,        0,           Button3,    toggleview,     {0} },
	{ ClkTagBar,        M,           Button1,    tag,            {0} },
	{ ClkTagBar,        M,           Button3,    toggletag,      {0} },
	{ ClkTagBar,        0,           Button4,    cycleiconset,   {.i = +1 } },
	{ ClkTagBar,        0,           Button5,    cycleiconset,   {.i = -1 } },
};
