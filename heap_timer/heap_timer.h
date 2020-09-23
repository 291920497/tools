#ifndef _HEAP_TIMER_H_
#define _HEAP_TIMER_H_

#ifdef _WIN32
#include <Windows.h>
#else
//�������_GNU_SOURCEԤ����
#include <pthread.h>
#endif//_WIN32

#include <stdint.h>



/*
�Ƿ����õ��߳�ģʽ,�����ǵ��߳�ʹ��ԭ������Ҳ������ʱ�����ģ������С
��ȷ���ڵ��̻߳�����ʹ�ã���Ȼ����������Ԥ����
*/
//#define HT_SINGLE_THREAD_MOD

typedef struct heap_obj heap_obj_t;

typedef struct timer_element {
	uint32_t timer_id;	//��ʱ��ID
	uint32_t interval;	//���ʱ��
	uint64_t ring_time;	//����ʱ��
	int32_t repeat;	//�ظ�����
	void* user_data;
	void(*on_timeout)(void*);
}timer_element_t;

typedef struct heap_timer {
	uint32_t unique_id;
	timer_element_t* running_timer;
	heap_obj_t* heap_timer_objs;

#ifndef HT_SINGLE_THREAD_MOD

#ifdef _WIN32
	CRITICAL_SECTION lock_hp_timer;
#else
	pthread_spinlock_t lock_hp_timer;
#endif//_WIN32

#endif//HT_SINGLE_THREAD_MOD
}heap_timer_t;

uint64_t get_local_ms();

heap_timer_t* create_heap_timer();

void destroy_heap_timer(heap_timer_t* ht);

/*
	return value:
	-1 failed;
	other timer_id;
*/
uint32_t ht_add_timer(heap_timer_t* ht, uint32_t interval, int32_t repeat, void(*on_timeout)(void*), void* user_data);

void ht_del_timer(heap_timer_t* ht, uint32_t timer_id);

void ht_del_timer_incallback(heap_timer_t* ht, uint32_t timer_id);

uint32_t ht_update_timer(heap_timer_t* ht);


#endif//_HEAP_TIMER_H_