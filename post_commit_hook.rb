#!/usr/bin/env ruby

require 'grit'
include Grit

puts 'Running tigger....'
puts 'Matching tasks and commit messages.'

repo = Repo.new('./')
commits = repo.commits

tigger = File.new('.tigger', 'r')
tasks = Array.new
completed_tasks = Array.new

tigger.each_line { |line|  tasks << line }

commit = commits.last
 
tasks.each do | task |                                                      
    if (commit.message.strip.upcase.index(task.strip.upcase) != nil)
      completed_tasks << (Time.now.to_i.to_s + "<?TIG?>" + task)
      tasks.delete task
      puts('Completed task: ' + task.strip + '.')
    end
end

tigger.close

tigger = File.new('.tigger', 'w')

tasks.each { |task| tigger.write task }

tigger.close

tigger_completed = File.new('.tigger_completed', 'a+')
completed_tasks.each { |task| tigger_completed.write task }
tigger_completed.close