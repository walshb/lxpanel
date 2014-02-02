/*
 * Copyright (c) 2014 LxDE Developers, see the file AUTHORS for details.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __PLUGIN_H__
#define __PLUGIN_H__ 1

#include <libfm/fm.h>

#include "panel.h"
#include "conf.h"

G_BEGIN_DECLS

/* New plugins style which uses FmModule loader, our module type is "lxpanel_gtk" */

#define FM_MODULE_lxpanel_gtk_VERSION 1 /* version of this API */

typedef struct {
    /*< public >*/
    void (*init)(void);         /* optional startup */
    void (*finalize)(void);     /* optional finalize */
    char *name;                 /* name to represent in lists */
    char *description;          /* tooltip text */
    GtkWidget *(*new_instance)(Panel *panel, config_setting_t *settings);
    void (*config)(Panel *panel, GtkWidget *instance, GtkWindow *parent);
    void (*reconfigure)(Panel *panel, GtkWidget *instance);
    int one_per_system : 1;     /* True to disable more than one instance */
    int expand_available : 1;   /* True if "stretch" option is available */
    int expand_default : 1;     /* True if "stretch" option is default */
    /*< private >*/
    gpointer _reserved1;
    gpointer _reserved2;
} LXPanelPluginInit; /* constant data */

extern LXPanelPluginInit fm_module_init_lxpanel_gtk;

extern GQuark lxpanel_plugin_qdata; /* access to plugin private data */
#define lxpanel_plugin_get_data(_i) g_object_get_qdata(G_OBJECT(_i),lxpanel_plugin_qdata)
#define lxpanel_plugin_set_data(_i,_data,_destructor) g_object_set_qdata_full(G_OBJECT(_i),lxpanel_plugin_qdata,_data,_destructor)

/* register new plugin type - can be called from plugins init() too */
extern gboolean lxpanel_register_plugin_type(const char *name, LXPanelPluginInit *init);

/* few helper functions */
extern GtkMenu* lxpanel_get_plugin_menu(Panel* panel, GtkWidget* plugin, gboolean use_sub_menu);
extern gboolean lxpanel_plugin_button_press_event(GtkWidget *widget, GdkEventButton *event, GtkWidget *plugin);
			/* Handler for "button_press_event" signal with Plugin as parameter */
extern void lxpanel_plugin_adjust_popup_position(GtkWidget * popup, GtkWidget * plugin);
			/* Helper to move popup windows away from the panel */
extern void lxpanel_plugin_popup_set_position_helper(Panel * p, GtkWidget * near, GtkWidget * popup, GtkRequisition * popup_req, gint * px, gint * py);
			/* Helper for position-calculation callback for popup menus */
extern void plugin_widget_set_background(GtkWidget * plugin, Panel * p);
			/* Recursively set the background of all widgets on a panel background configuration change */

G_END_DECLS

#endif /* __PLUGIN_H__ */
