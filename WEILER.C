#include <stdio.h>
#include <graphics.h>
#include <conio.h>

struct vertex
{
    float x;
    float y;
    int entr_leav;
    int intersection; // entering or leaving,intersection flags
};

void draw_poly(int n, struct vertex vlist[])
{
    int i;
    for (i = 0; i < n; i++)
    {
        line(vlist[i].x, vlist[i].y, vlist[(i + 1) % n].x, vlist[(i + 1) % n].y);
    }
}

void cyrus_beck(int n, struct vertex cw[], struct vertex p1, struct vertex p2)
{
    int i;
    float t_enter = 0, t_leave = 1;
    struct vertex pe, pl, xy[2]; // vertex entering and leaving
    for (i = 0; i < n; i++)
    {
        struct vertex norm, pei; // normal,edge
        float num, den, t;       // numerator,denominator,t value
        pei = cw[i];
        norm.x = cw[i + 1].y - cw[i].y;
        norm.y = cw[i + 1].x - cw[i].x;
        num = norm.x * (pei.x - p1.x) - norm.y * (pei.y - p1.y);
        den = norm.x * (p2.x - p1.x) + norm.y * (p1.y - p2.y);
        if (den != 0)
        {
            t = (num * 1.0) / den;
        }
        if (t >= 0 && t <= 1)
        {
            if (den < 0)
            {
                if (t > t_enter)
                {
                    t_enter = t;
                }
            }
            else if (den > 0)
            {
                if (t < t_leave)
                {
                    t_leave = t;
                }
            }
        }
    }
    pe.x = p1.x + (p2.x - p1.x) * t_enter;
    pe.y = p1.y + (p2.y - p1.y) * t_enter;
    xy[0].x = pe.x;
    xy[0].y = pe.y;
    pl.x = p1.x + (p2.x - p1.x) * t_leave;
    pl.y = p1.y + (p2.y - p1.y) * t_leave;
    xy[1].x = pl.x;
    xy[1].y = pl.y;
    draw_poly(2, xy);
}


void main()
{
    int gd = DETECT, gm, xmin, ymin, xmax, ymax, sp_n, i;
    struct vertex cw[20], sp[20];
    clrscr();
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    printf("enter coordinates of clipping window xmin,ymin,xmax,ymax: ");
    scanf("%d%d%d%d", &xmin, &ymin, &xmax, &ymax);
    cw[0].x = xmin;
    cw[0].y = ymin;
    cw[1].x = xmax;
    cw[1].y = ymin;
    cw[2].x = xmax;
    cw[2].y = ymax;
    cw[3].x = xmin;
    cw[3].y = ymax;
    printf("Enter no. of vertices in subject polygon: ");
    scanf("%d", &sp_n);
    printf("Enter vertices (x,y) clockwise: ");
    for (i = 0; i < sp_n; i++)
    {
        scanf("%d%d", &sp[i].x, &sp[i].y);
    }
    for (i = 0; i < sp_n; i++)
    {
        cyrus_beck(4, cw, sp[i], sp[(i + 1) % sp_n]);
    }
    getch();
}
