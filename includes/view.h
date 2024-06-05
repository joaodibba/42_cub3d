#ifndef VIEW_H
# define VIEW_H

#ifndef WIN_WIDTH
# define WIN_WIDTH 800
#endif

#ifndef WIN_HEIGHT
# define WIN_HEIGHT 600
#endif



// function definations
void	put_pixel(t_image *img, int x, int y, int color);
void	draw_square(t_image *img, int x, int y, int size, int color);

#endif