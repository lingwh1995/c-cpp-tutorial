#ifndef MYLIB_2_H
#define MYLIB_2_H
/*
 * 从数组中查找当前值，查找到返回数组索引，查找不到返回-1
 * @param *arr 代表数组的指针
 * @param n 当前元素在目标数组中的索引
 * @param num 要确定是否存在于当前数组中的值
 */
int find_value_3(const int *arr, int n, int num);

/*
 * 初始化数组
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
extern void init_arr_3(int *arr, int len);

/*
 * 交换两个数
 * @param *pa 代表第一个数的指针
 * @param *pb 代表第二个数的指针
 */
extern void swap_number__3(int *pa, int *pb);

/*
 * 冒泡排序
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
extern void bubble_sort_3(int *arr, int len);

/*
 * 打印数组
 * @param *arr 代表数组的指针
 * @param len 数组长度
 */
extern void print_arr_3(const int *arr, const int len);
#endif // !MYLIB_2_H
