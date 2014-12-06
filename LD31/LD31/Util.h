// Delete a pointer with null checking
template <typename T>
void safe_delete(T* m)
{
	if(m != nullptr)
		delete m;
}