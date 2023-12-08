/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "HackNerdFont:size=9:style=Bold" };
static const char dmenufont[]       = "HackNerdFont:size=9:style=Bold";
static const char col_gray1[]       = "#161515"; /*191e25*/
static const char col_gray2[]       = "#c6c6c6";
static const char col_gray3[]       = "#000000";
static const char col_gray4[]       = "#506980";
static const char col_cyan[]        = "#2D3A46";/*607190*/
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray2, col_gray3, col_gray1 },
	[SchemeSel]  = { col_gray4, col_gray3,  col_cyan  },
};

static const char *const autostart[] = {
  "dunst", NULL,
  "nitrogen", "--restore", NULL,
  "sh", "-c", "~/.config/dunst/scripts/low_bat_notifier.sh", NULL,
	"/usr/bin/lxpolkit", NULL,
	NULL /* terminate */
};



/* tagging */
/*static const char *tags[] = { "0", "1", "2", "3", "4"};*/
/*static const char *tags[] = { "α", "β", "γ", "δ", "ε", "ζ", "η", "θ", "ι" };*/
static const char *tags[] = { "term", "www", "vmc", "mus", "fm", "irc", "recs", "foo", "bar" };
/* static const char *tags[] = { "ぜろ", " いち", "に", "さん", "し", "ご", "ろく", "しち", "はち" }; */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "rofi", "-show","drun", NULL };
/* static const char *termcmda[]  = { "st", NULL }; */
static const char *termcmd[]  = { "kitty", NULL };
static const char *web[]  = { "chromium", NULL };
static const char *flame[] =   { "flameshot", "gui", NULL };
static const char *files[] =   { "thunar", NULL };
static const char *pass[] =   { "keepassxc", NULL };
static const char *img[] =   { "phototonic", NULL };
static const char *vol[] =   { "pavucontrol", NULL };
static const char *wal[] =   { "nitrogen", NULL };
static const char *apa[] =   { "lxappearance", NULL };
/* static const char *idea[] =   { "sh /opt/idea/bin/idea.sh", NULL }; */


static const Key keys[] = {
	/* modifier                     key        function        argument */

  { MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		      XK_Return, spawn,          {.v = termcmd } },
	/* { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmda } }, */
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = web } },
  { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = files } },
  { MODKEY|ShiftMask,             XK_r,      spawn,          {.v = img } },
  { MODKEY|ShiftMask,             XK_k,      spawn,          {.v = pass } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = flame } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = vol } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = wal } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = apa } },



	/* { MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("sh /opt/idea/bin/idea.sh") }, */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_c,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
  	{MODKEY|ControlMask|ShiftMask,  XK_q,      quit,           {0} }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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
