#!/usr/bin/env ruby
class Node
    attr_reader :id
    attr_accessor :visited,:neighbors
    
    
    def initialize(id,neighbors=[])
        @visited = false
        @id = id
        @neighbors = neighbors
    end
end
a = Node.new(:a)
b = Node.new(:b)
c = Node.new(:c)
d = Node.new(:d)
e = Node.new(:e)
f = Node.new(:f)
g = Node.new(:g)
h = Node.new(:h)
a.neighbors = [b,d,g]
b.neighbors = [f,a,e]
c.neighbors = [f,h]
d.neighbors = [a,f]
e.neighbors = [b,g]
f.neighbors = [b,c,d]
g.neighbors = [a,e]
h.neighbors = [c]
queue = []
queue << a
while !queue.empty? do
    node = queue.shift
    puts node.id
    node.visited = true
    neighbors = node.neighbors.sort {|x,y| x.id <=> y.id }
    neighbors.each { |neighbor|
        if (neighbor.visited)
           nil # do nothing
        else
            neighbor.visited = true
            queue << neighbor 
        end
    }
end

