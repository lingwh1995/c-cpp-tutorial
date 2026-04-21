#ifndef MYLIB_1_H
#define MYLIB_1_H
/*
 * 初始化数组
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
extern void init_arr_2(int *arr, int len);

/*
 * 交换两个数
 * @param *pa 代表第一个数的指针
 * @param *pb 代表第二个数的指针
 */
extern void swap_number_2(int *pa, int *pb);

/*
 * 冒泡排序
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
extern void bubble_sort_2(int *arr, int len);

/*
 * 打印数组
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
extern void print_arr_2(const int *arr, const int len);
#endif // !MYLIB_1_H
