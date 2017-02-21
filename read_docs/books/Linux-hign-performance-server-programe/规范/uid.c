#include <unistd.h>
#include <stdio.h>

int main() {
    uid_t uid = getuid();
    uid_t euid = geteuid();

    printf("uid is %d, euid is :%d", uid, euid);

    return 0;
}


static bool switch_to_user (uid_t user_id, gid_t gp_id) {
    //确保用户不是root
    if ((user_id == 0) && (gp_id == 0)) {
        return false;
    }

    //确保当前用户是合法用户:root 或者目标用户
    gid_t gid = getgid();
    uid_t uid = getuid();
    if ((gid != 0 || uid != 0) && (gid != gp_id || uid != user_id)) {
        return false;
    }

    //如果不是root,则已经是目标用户
    if (uid != 0) {
        return true;
    }

    //切换到目标用户
    if ((setgid(gp_id) < 0) || (getuid(user_id) < 0)) {
        return false;
    }

    return true;
}

pid_t getpgid(pid_t pid);
/**
 * 用户进程的进程组id
 * @param  pid  0设置当前进程，如果pid=pgid,则pid为进程组首领
 * @param  pgid 进程组id
 * @return
 */
int setpgid(pid_t pid, pid_t pgid);
