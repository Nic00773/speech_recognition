#ifndef GNUPLOT_H_
#define GNUPLOT_H_

void print_graph (float * data, int data_size, char * graph_name, char * png_name);
void print_signal (float * data, int data_size, int duration, char * graph_name, char * png_name);

#endif
