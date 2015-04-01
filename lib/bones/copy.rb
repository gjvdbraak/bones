
module Bones
	
	# Class copyin/out
	class Copy
		attr_accessor :scop, :name, :domain, :deadline, :direction, :id
		
		def initialize(scop,name,domain,deadline,direction,id)
			@scop = scop
			@name = name
			@domain = domain
			@deadline = deadline
			@direction = direction
			@id = id
		end
		
		def get_definition(array_definition,type)
			array_definition = '' if type == 'free' || type == 'alloc'
			'void bones_'+type+'_'+@id+'_'+@name+'('+array_definition+');'
		end
		
		def get_function_call(type)
			'bones_'+type+'_'+@id+'_'+@name+'();'
		end
	end
	
end