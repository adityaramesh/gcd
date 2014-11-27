require 'rake/clean'

cxx       = ENV['CXX']
boost     = ENV['BOOST_INCLUDE_PATH']
ccbase    = ENV['CCBASE_INCLUDE_PATH']
langflags = "-std=c++11"
wflags    = "-Wall -Wextra"
archflags = "-march=native"
incflags  = "-I. -I#{ccbase} -I#{boost}"
libflags  = ""
ppflags   = ""
dbflags   = "-O0 -ggdb"
optflags  = "-O3"
ldflags   = ""
cxxflags  = "#{langflags} #{wflags} #{archflags} #{incflags} #{libflags} #{ppflags} #{optflags}"

dirs  = ["bin"]
tests = FileList["test/*"].map{|f| f.sub("test", "bin").ext("run")}

task :default => dirs + tests

dirs.each do |d|
	directory d
end

tests.each do |f|
	src = f.sub("bin", "test").ext("cpp")
	file f => ["bin"] + [src] do
		sh "#{cxx} #{cxxflags} -o #{f} #{src} #{ldflags}"
	end
end

task :clobber => ["bin"] do
	FileList["bin/*"].each{ |f| File.delete(f) if File.file?(f) }
end
