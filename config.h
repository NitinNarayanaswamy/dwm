/* See LICENSE file for copyright and license details. */

/* include */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Noto Sans Mono Medium:size=14" };
static const char dmenufont[]       = "Noto Sans Mono Medium:size=14";

/* orange-theme, palette from https: https://coolors.co/3d5a80-98c1d9-e0fbfc-ee6c4d-293241 */
static const char col_bg[]      = "#293241";
static const char col_theme[]   = "#EE6C4D";
static const char col_fg[]      = "#98C1D9";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]        = { col_fg, col_bg, col_bg },
	[SchemeSel]         = { col_theme, col_bg, col_theme },
	[SchemeStatus]      = { col_fg, col_bg, "#000000" },
	[SchemeTagsSel]     = { col_bg, col_theme, "#000000" },
	[SchemeTagsNorm]    = { col_fg, col_bg, "#000000" },
	[SchemeInfoSel]     = { col_theme, col_bg, "#000000" },
	[SchemeInfoNorm]    = { col_fg, col_bg, "#000000" },
};

/* nebula-orange-theme, based on https://imgur.com/FUd52am */
//static const char col_bg[]      = "#26203C";
//static const char col_theme[]   = "#E57861";
//static const char col_fg[]      = "#34AEA3";
//
//static const char *colors[][3]      = {
//	/*               fg         bg         border   */
//	[SchemeNorm]        = { col_fg, col_bg, col_bg },
//	[SchemeSel]         = { col_theme, col_bg, col_fg },
//	[SchemeStatus]      = { col_theme, col_bg, "#000000" },
//	[SchemeTagsSel]     = { col_bg, col_fg, "#000000" },
//	[SchemeTagsNorm]    = { col_theme, col_bg, "#000000" },
//	[SchemeInfoSel]     = { col_fg, col_bg, "#000000" },
//	[SchemeInfoNorm]    = { col_fg, col_bg, "#000000" },
//};

/* nebula-turquoise-theme, based on https://imgur.com/FUd52am */
//static const char col_bg[]      = "#26203C";
//static const char col_theme[]   = "#34AEA3";
//static const char col_fg[]      = "#1D6573";
//
//static const char *colors[][3]      = {
//	/*               fg         bg         border   */
//	[SchemeNorm]        = { col_fg, col_bg, col_bg },
//	[SchemeSel]         = { col_theme, col_bg, col_theme },
//	[SchemeStatus]      = { col_theme, col_bg, "#000000" },
//	[SchemeTagsSel]     = { col_bg, col_theme, "#000000" },
//	[SchemeTagsNorm]    = { col_fg, col_bg, "#000000" },
//	[SchemeInfoSel]     = { col_theme, col_bg, "#000000" },
//	[SchemeInfoNorm]    = { col_fg, col_bg, "#000000" },
//};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T",      tile },    /* first entry is default */
	{ "F",      NULL },    /* no layout function means floating behavior */
	{ "M",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_bg, "-sf", col_theme, NULL };
static const char *termcmd[]  = { "st", NULL };

/* my_commands */
static const char *browsercmd[] = { "firefox", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ 0, XF86XK_AudioMute,                     spawn,          SHCMD("amixer -q set Master toggle && kill -10 $(pidof -x dwmbar)") },
	{ 0, XF86XK_AudioRaiseVolume,              spawn,          SHCMD("amixer -q set Master 5%+ unmute && kill -10 $(pidof -x dwmbar)") },
	{ 0, XF86XK_AudioLowerVolume,              spawn,          SHCMD("amixer -q set Master 5%- unmute && kill -10 $(pidof -x dwmbar)") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

