#define POST_COMMIT_HOOK \
"#!/usr/bin/env ruby\n" \
"\n" \
"require 'grit'\n" \
"include Grit\n" \
"\n" \
"puts 'Running tigger....'\n" \
"puts 'Matching tasks and commit messages.'\n" \
"\n" \
"repo = Repo.new('./')\n" \
"commits = repo.commits\n" \
"\n" \
"tigger = File.new('.tigger', 'r')\n" \
"tasks = Array.new\n" \
"completed_tasks = Array.new\n" \
"\n" \
"tigger.each_line { |line|  tasks << line }\n" \
"\n" \
"commit = commits.last\n" \
" \n" \
"tasks.each do | task |                                                      \n" \
"    if (commit.message.strip.upcase.index(task.strip.upcase) != nil)\n" \
"      completed_tasks << (Time.now.to_i.to_s + \"<?TIG?>\" + task)\n" \
"      tasks.delete task\n" \
"      puts('Completed task: ' + task.strip + '.')\n" \
"    end\n" \
"end\n" \
"\n" \
"tigger.close\n" \
"\n" \
"tigger = File.new('.tigger', 'w')\n" \
"\n" \
"tasks.each { |task| tigger.write task }\n" \
"\n" \
"tigger.close\n" \
"\n" \
"tigger_completed = File.new('.tigger_completed', 'a+')\n" \
"completed_tasks.each { |task| tigger_completed.write task }\n" \
"tigger_completed.close\n" \
""
