def raise_exception
	begin
	puts 'i am before the raise'
	puts 'i am after the raise'
	rescue
		puts 'i am rescued'
	end
	puts 'i am after the begin block'
end
raise_exception
