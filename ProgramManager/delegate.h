#pragma once

namespace ProgramManager
{
	struct MessageArgs;

	class FunctionBase
	{
	protected:
		bool mSet = true;
	public:
		virtual ~FunctionBase() {}

		virtual void ExecuteSet(MessageArgs args) = 0;
		virtual void ExecuteGet(MessageArgs& args) = 0;
	};

	template <typename T>
	class FunctionMeta : public FunctionBase
	{
	public:
		typedef void(T::* functionSet)(MessageArgs);
		typedef void(T::* functionGet)(MessageArgs&);

	private:
		T* mCaller				 = nullptr;
		functionSet mFunctionSet = nullptr;
		functionGet mFunctionGet = nullptr;

	public:
		FunctionMeta(T* caller, functionSet set) : mCaller(caller), mFunctionSet(set) { mSet = true; }
		FunctionMeta(T* caller, functionGet get) : mCaller(caller), mFunctionGet(get) { mSet = false; }

		virtual void ExecuteSet(MessageArgs args) override
		{
			if (mCaller && mFunctionSet) {
				(mCaller->*mFunctionSet)(args);
			}
		}
		virtual void ExecuteGet(MessageArgs& args) override
		{
			if (mCaller && mFunctionGet) {
				(mCaller->*mFunctionGet)(args);
			}
		}
	};

	class Delegate
	{
		FunctionBase* mDelegate = nullptr;
		int           mFunctionId = -1;
	public:

		template <typename T>
		Delegate(T* caller, void(T::* f)(MessageArgs), int id) : mFunctionId(id)
		{
			mDelegate = new FunctionMeta<T>(caller, f);
		}

		template <typename T>
		Delegate(T* caller, void(T::* f)(MessageArgs &), int id) : mFunctionId(id)
		{
			mDelegate = new FunctionMeta<T>(caller, f);
		}

		void ExecuteSet(MessageArgs args);
		void ExecuteGet(MessageArgs& args);

		int GetFunctionId() const { return mFunctionId; }
	};
}