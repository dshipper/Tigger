#!/usr/bin/env ruby

####################################
# rb2h.                            #
#                                  #
# Created by Tim Raymond on 7/4/11 #
####################################

macro_name = ARGV[0]
filename = macro_name.downcase + '.rb'

unless macro_name =~ /\w+/ && ARGV.length == 1
  puts 'Usage: rb2h MACRO_NAME'
  puts 'Macros should be comprised of characters A-Z, a-z, 0-9, and underscore (_)'
  exit(1)
end

File.open(filename.sub(/.rb/, '.h'), 'w') do |header_file|
  File.open(filename) do |file|
    header_file.write('#define ' + macro_name + " \\\n")  #begin the macro definition
  
    file.readlines.each do |line|
        line.chomp!
        line.gsub!(/"/, '\"')       #properly escape quotes and slashes
        line.gsub!(/\\/, '\\\\')
        header_file.write('"' + line + "\\n" + '"'+ " \\\n")
    end
  
    header_file.write("\"\"\n")   #end the macro definition
  end
end
