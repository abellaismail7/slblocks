#include "coutil.h"

const uintmax_t ram_free(void);
const uintmax_t ram_perc(void);
const uintmax_t ram_total(void);
const uintmax_t ram_used(void);

const char * free_mem(void){
	double used = (double) ram_used();
	int prefix = 1024;
	v_human(&used,&prefix);
	sprintf(buf,"%s %0.1f %ci","",used,prefix);
	return buf;
}

#if defined(__linux__)
	#include <stdint.h>

	const uintmax_t ram_free(void)
	{
		uintmax_t free;

		if (pscanf("/proc/meminfo",
		           "MemTotal: %ju kB\n"
		           "MemFree: %ju kB\n"
		           "MemAvailable: %ju kB\n",
		           &free, &free, &free) != 3) {
			return -1;
		}

		return free * 1024;
	}

	const uintmax_t ram_perc(void)
	{
		uintmax_t total, free, buffers, cached;

		if (pscanf("/proc/meminfo",
		           "MemTotal: %ju kB\n"
		           "MemFree: %ju kB\n"
		           "MemAvailable: %ju kB\n"
		           "Buffers: %ju kB\n"
		           "Cached: %ju kB\n",
		           &total, &free, &buffers, &buffers, &cached) != 5) {
			return -1;
		}

		if (total == 0) {
			return -1;
		}

		return 100 * ((total - free) - (buffers + cached)) / total;
	}

	const uintmax_t ram_total(void)
	{
		uintmax_t total;

		if (pscanf("/proc/meminfo", "MemTotal: %ju kB\n", &total)
		    != 1) {
			return -1;
		}

		return total * 1024;
	}

	const uintmax_t ram_used(void)
	{
		uintmax_t total, free, buffers, cached;

		if (pscanf("/proc/meminfo",
		           "MemTotal: %ju kB\n"
		           "MemFree: %ju kB\n"
		           "MemAvailable: %ju kB\n"
		           "Buffers: %ju kB\n"
		           "Cached: %ju kB\n",
		           &total, &free, &buffers, &buffers, &cached) != 5) {
			return -1;
		}

		return (total - free - buffers - cached) * 1024;
	}
#elif defined(__OpenBSD__)
	#include <stdlib.h>
	#include <sys/sysctl.h>
	#include <sys/types.h>
	#include <unistd.h>

	#define LOG1024 10
	#define pagetok(size, pageshift) (size_t)(size << (pageshift - LOG1024))

	inline int
	load_uvmexp(struct uvmexp *uvmexp)
	{
		int uvmexp_mib[] = {CTL_VM, VM_UVMEXP};
		size_t size;

		size = sizeof(*uvmexp);

		if (sysctl(uvmexp_mib, 2, uvmexp, &size, NULL, 0) >= 0) {
			return 1;
		}

		return 0;
	}

	const uintmax_t ram_free(void)
	{
		struct uvmexp uvmexp;
		int free_pages;

		if (load_uvmexp(&uvmexp)) {
			free_pages = uvmexp.npages - uvmexp.active;
			return pagetok(free_pages, uvmexp.pageshift) *
			                 1024;
		}

		return -1;
	}

	const uintmax_t ram_perc(void)
	{
		struct uvmexp uvmexp;
		int percent;

		if (load_uvmexp(&uvmexp)) {
			percent = uvmexp.active * 100 / uvmexp.npages;
			return percent;
		}

		return -1;
	}

	const uintmax_t ram_total(void)
	{
		struct uvmexp uvmexp;

		if (load_uvmexp(&uvmexp)) {
			return pagetok(uvmexp.npages,
			                         uvmexp.pageshift) * 1024;
		}

		return -1;
	}

	const uintmax_t ram_used(void)
	{
		struct uvmexp uvmexp;

		if (load_uvmexp(&uvmexp)) {
			return pagetok(uvmexp.active,
			                         uvmexp.pageshift) * 1024;
		}

		return -1;
	}
#elif defined(__FreeBSD__)
	#include <sys/sysctl.h>
	#include <sys/vmmeter.h>
	#include <unistd.h>
	#include <vm/vm_param.h>

	const uintmax_t ram_free(void) {
		struct vmtotal vm_stats;
		int mib[] = {CTL_VM, VM_TOTAL};
		size_t len;

		len = sizeof(struct vmtotal);
		if (sysctl(mib, 2, &vm_stats, &len, NULL, 0) == -1
				|| !len)
			return -1;

		return vm_stats.t_free * getpagesize();
	}

	const uintmax_t ram_total(void) {
		long npages;
		size_t len;

		len = sizeof(npages);
		if (sysctlbyname("vm.stats.vm.v_page_count", &npages, &len, NULL, 0) == -1
				|| !len)
			return -1;

		return npages * getpagesize()
	}

	const uintmax_t ram_perc(void) {
		long npages;
		long active;
		size_t len;

		len = sizeof(npages);
		if (sysctlbyname("vm.stats.vm.v_page_count", &npages, &len, NULL, 0) == -1
				|| !len)
			return -1;

		if (sysctlbyname("vm.stats.vm.v_active_count", &active, &len, NULL, 0) == -1
				|| !len)
			return -1;

		return active * 100 / npages;
	}

	const uintmax_t ram_used(void) {
		long active;
		size_t len;

		len = sizeof(active);
		if (sysctlbyname("vm.stats.vm.v_active_count", &actve, &len, NULL, 0) == -1
				|| !len)
			return -1;

		return active * getpagesize();
	}
#endif
