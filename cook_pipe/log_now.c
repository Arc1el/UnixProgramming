void log_now(int select, char menu[])
{

        int time_fd;
        time_t t;
        struct tm tm;
        char logbuf[BUFSIZ];

        //로그파일을 남기기위한 log.txt를 open
        time_fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND , 0644 );
        if(time_fd == -1)
        {
                perror("open log file");
                exit(6);
        }

        t = time(NULL);
        tm = *localtime(&t);
        if(select == 0) //주문전달
        {
                sprintf(logbuf, "%d년 %d월 %d일 %d시 %d분 %d초 주문전달 메뉴 : %s",
                                tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour,
                                tm.tm_min, tm.tm_sec, menu);
        }
        else if(select == 1)//주문완료
        {
                sprintf(logbuf, "%d년 %d월 %d일 %d시 %d분 %d초 주문완료\n",
                                tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour,
                                tm.tm_min, tm.tm_sec);
        }
        write(time_fd, logbuf, strlen(logbuf));
        close(time_fd);
}
