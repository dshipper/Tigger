/*
 *  tigger_util.h
 *  Tigger
 *
 *  Created by Dan Shipper on 6/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


char * commit_hook = "#!/usr/bin/env ruby \n"

"require 'grit' \n"
"include Grit \n"

"puts 'Running tigger....' \n"
"puts 'Matching tasks and commit messages.' \n"

"repo = Repo.new('./') \n"
"commits = repo.commits \n"

"tigger = File.new('.tigger', 'r') \n"
"tasks = Array.new \n"
"completed_tasks = Array.new \n"

"tigger.each_line { |line|  tasks << line } \n"

"tasks.each do | task | \n"
"commits.each do | commit | \n"                                                         
"if (task.strip.upcase == commit.message.strip.upcase) \n"
"completed_tasks << task \n"
"tasks.delete task \n" 
"puts('Completed task: ' + commit.message + '.')\n "
"end \n"
"end  \n"  
"end\n "

"tigger.close\n "

"tigger = File.new('.tigger', 'w') \n"

"tasks.each { |task| tigger.write task } \n"

"tigger.close  \n"

"tigger_completed = File.new('.tigger_completed', 'a+') \n"
"completed_tasks.each { |task| tigger_completed.write task } \n"
"tigger_completed.close ";