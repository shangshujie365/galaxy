// Copyright (c) 2015, Galaxy Authors. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: wangtaize@baidu.com


#ifndef AGENT_CGROUP_H
#define AGENT_CGROUP_H

#include <vector>
#include <map>
#include <string>
#include "agent/task_runner.h"
#include "proto/task.pb.h"
#include "agent/workspace.h"
#include "common/mutex.h"

namespace galaxy {
class CGroupCtrl {
public:
    CGroupCtrl(std::string cg_root,std::vector<std::string> support_cg)
             :_cg_root(cg_root),_support_cg(support_cg){}
    ~CGroupCtrl() {}
    //create a cgroup,return subsystem name -> fs path map
    int Create(int64_t task_id,std::map<std::string,std::string>& sub_sys_map);
    //destroy a cgroup
    int Destroy(int64_t task_id);


private:
    std::string _cg_root;
    std::vector<std::string> _support_cg;
};

class AbstractCtrl{

public:
    AbstractCtrl(std::string my_cg_root):_my_cg_root(my_cg_root){}
    int AttachTask(pid_t pid);
    ~AbstractCtrl(){}
protected:
    std::string _my_cg_root;
};


class MemoryCtrl:public AbstractCtrl{
public:
    MemoryCtrl(std::string my_cg_root)
              :AbstractCtrl(my_cg_root){}
    //update memory.limit_in_bytes.
    int SetLimit(int64_t limit);
    //update memory.soft_limit_in_bytes.
    int SetSoftLimit(int64_t soft_limit);
    ~MemoryCtrl(){}
};

class CpuCtrl:public AbstractCtrl{

public:
    CpuCtrl(std::string my_cg_root)
    :AbstractCtrl(my_cg_root){}
    int SetCpuShare(int64_t cpu_share);
    int SetCpuPeriod(int64_t cpu_period);
    int SetCpuQuota(int64_t cpu_quota);
    ~CpuCtrl(){}
};




class ContainerTaskRunner:public AbstractTaskRunner{

public:
    ContainerTaskRunner(TaskInfo task_info,
                        std::string cg_root,
                        DefaultWorkspace* workspace)
                       :AbstractTaskRunner(task_info,workspace),
                        _cg_root(cg_root){}
    int Prepare();
    int Start();
    int Stop();
    ~ContainerTaskRunner(){
        delete _cg_ctrl;
        delete _mem_ctrl;
        delete _cpu_ctrl;
    }
private:
    void PutToCGroup();
private:
    std::string _cg_root;
    CGroupCtrl* _cg_ctrl;
    MemoryCtrl* _mem_ctrl;
    CpuCtrl*    _cpu_ctrl;
};

}
#endif
