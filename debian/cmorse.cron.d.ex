#
# Regular cron jobs for the cmorse package
#
0 4	* * *	root	[ -x /usr/bin/cmorse_maintenance ] && /usr/bin/cmorse_maintenance
