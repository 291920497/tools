#include <stdio.h>
#include <stdint.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/select.h>
#endif//_WIN32

#include "heap_timer.h"

heap_timer_t* ht;

void test_timer_func(void* user_data) {
	printf("%d\n", user_data);
	//ht_del_timer(user_data, 0);
	if (user_data == 3) {
		ht_del_timer_incallback(ht, 2);
	}
}

int main() {

	/*uint64_t t = get_local_ms();

	Sleep(7500);
	uint64_t t2 = get_local_ms();

	printf("%lld\n", t2 - t);*/


	ht = create_heap_timer();

	ht_add_timer(ht, 1000, -1, test_timer_func, 1);
	ht_add_timer(ht, 2000, 2, test_timer_func, 2);
	ht_add_timer(ht, 3000, 3, test_timer_func, 3);
	ht_add_timer(ht, 4000, 4, test_timer_func, 4);
	ht_add_timer(ht, 5000, 5, test_timer_func, 5);
	ht_add_timer(ht, 6000, 6, test_timer_func, 6);
	ht_add_timer(ht, 7000, 7, test_timer_func, 7);
	ht_add_timer(ht, 8000, 8, test_timer_func, 8);

	while (1) {
		uint32_t slp_time = ht_update_timer(ht);
		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = slp_time * 1000;
		select(0, 0, 0, 0, &tv);
	}

	destroy_heap_timer(ht);
	return 0;
}