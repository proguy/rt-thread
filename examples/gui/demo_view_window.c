#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include "demo_view.h"

static struct rtgui_timer *timer;
static struct rtgui_label* label;
static struct rtgui_win* msgbox = RT_NULL;
static rt_uint8_t label_text[80];
static int cnt = 5;

void window_demo_close(struct rtgui_widget* widget, rtgui_event_t *even)
{
	rtgui_win_t* win;

	/* ������ؼ� */
	win = RTGUI_WIN(rtgui_widget_get_toplevel(widget));

	/* ���ٴ��� */
	rtgui_win_destroy(win);
}

/* �رնԻ���ʱ�Ļص����� */
void diag_close(struct rtgui_timer* timer, void* parameter)
{
	sprintf(label_text, "closed then %d second!", cnt);

	rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
	if (cnt == 0)
	{
		rtgui_win_destroy(msgbox);
		rtgui_timer_stop(timer);
		rtgui_timer_destory(timer);
	}

	cnt --;
}

void window_demo_autoclose(rtgui_toplevel_t* parent)
{
#if 0
	struct rtgui_rect rect = {50, 50, 200, 200};

	msgbox = rtgui_win_create(parent, "Information", &rect, RTGUI_WIN_STYLE_DEFAULT);
	if (msgbox != RT_NULL)
	{
		struct rtgui_box* box = rtgui_box_create(RTGUI_VERTICAL, RT_NULL);

		cnt = 5;
		sprintf(label_text, "closed then %d second!", cnt);
		label = rtgui_label_create(label_text);

		rtgui_win_set_box(msgbox, box);
		RTGUI_WIDGET(label)->align = RTGUI_ALIGN_CENTER_HORIZONTAL |
			RTGUI_ALIGN_CENTER_VERTICAL;
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(label),130);
		rtgui_box_append(box, RTGUI_WIDGET(label));
		rtgui_box_layout(box);

		rtgui_win_show(msgbox, RT_FALSE);
	}

	timer = rtgui_timer_create(200, RT_TIMER_FLAG_PERIODIC, diag_close, RT_NULL);
	rtgui_timer_start(timer);
#endif
}

static rt_uint16_t delta_x = 20;
static rt_uint16_t delta_y = 40;

/* ��ʾ�������� */
void window_demo_normal(rtgui_toplevel_t* parent)
{
	rtgui_win_t *win;
	rtgui_label_t *label;
	rtgui_rect_t rect = {0, 0, 150, 80};

	rtgui_rect_moveto(&rect, delta_x, delta_y);
	delta_x += 20; delta_y += 20;

	/* ����һ������ */
	win = rtgui_win_create(parent,
		"����", &rect, RTGUI_WIN_STYLE_DEFAULT);

	rect.x1 += 20; rect.x2 -= 5;
	rect.y1 += 5; rect.y2 = rect.y1 + 20;

	label = rtgui_label_create("����һ����ͨ����");
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));

	/* ��ģ̬��ʾ���� */
	rtgui_win_show(win, RT_FALSE);
}

void window_demo_modal(rtgui_toplevel_t* parent)
{
	rtgui_win_t *win;
	rtgui_label_t *label;
	rtgui_rect_t rect = {0, 0, 150, 80};

	rtgui_rect_moveto(&rect, delta_x, delta_y);
	delta_x += 20; delta_y += 20;

	/* ����һ������ */
	win = rtgui_win_create(parent,
		"ģʽ����", &rect, RTGUI_WIN_STYLE_DEFAULT);

	rect.x1 += 20; rect.x2 -= 5;
	rect.y1 += 5; rect.y2 = rect.y1 + 20;

	label = rtgui_label_create("����һ��ģʽ����");
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));

	/* ģ̬��ʾ���� */
	rtgui_win_show(win, RT_TRUE);
}

void window_demo_notitle(rtgui_toplevel_t* parent)
{
	rtgui_win_t *win;
	rtgui_label_t *label;
	rtgui_button_t *button;
	rtgui_rect_t rect = {0, 0, 150, 80};

	rtgui_rect_moveto(&rect, delta_x, delta_y);
	delta_x += 20; delta_y += 20;

	/* ����һ������ */
	win = rtgui_win_create(parent,
		"no title", &rect, RTGUI_WIN_STYLE_NO_TITLE | RTGUI_WIN_STYLE_NO_BORDER);
	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(win)) = white;

	/* ����һ���ı���ǩ */
	rect.x1 += 20; rect.x2 -= 5;
	rect.y1 += 5; rect.y2 = rect.y1 + 20;
	label = rtgui_label_create("�ޱ߿򴰿�");
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));

	/* ����һ���رհ�ť */
	rect.x1 += 20; rect.x2 = rect.x1 + 40;
	rect.y1 += 35; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("�ر�");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(button));
	rtgui_button_set_onbutton(button, window_demo_close);

	/* ��ģ̬��ʾ���� */
	rtgui_win_show(win, RT_FALSE);
}

static void demo_win_onbutton(struct rtgui_widget* widget, rtgui_event_t* event)
{
    window_demo_normal(RTGUI_TOPLEVEL(rtgui_widget_get_toplevel(widget)));
}

static void demo_autowin_onbutton(struct rtgui_widget* widget, rtgui_event_t* event)
{
	// window_demo_autoclose(RTGUI_TOPLEVEL(rtgui_widget_get_toplevel(widget)));
}

static void demo_modalwin_onbutton(struct rtgui_widget* widget, rtgui_event_t* event)
{
	window_demo_modal(RTGUI_TOPLEVEL(rtgui_widget_get_toplevel(widget)));
}

static void demo_ntitlewin_onbutton(struct rtgui_widget* widget, rtgui_event_t* event)
{
	window_demo_notitle(RTGUI_TOPLEVEL(rtgui_widget_get_toplevel(widget)));
}

rtgui_view_t* demo_view_window(rtgui_workbench_t* workbench)
{
    rtgui_rect_t  rect;
    rtgui_view_t* view;
    rtgui_button_t *button;

    view = demo_view(workbench, "Window Demo");

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("Normal Win");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, demo_win_onbutton);

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("Auto Win");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, demo_autowin_onbutton);

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25 + 25; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("Modal Win");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, demo_modalwin_onbutton);

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25 + 25 + 25; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("NoTitle Win");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, demo_ntitlewin_onbutton);

    return view;
}