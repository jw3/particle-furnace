#pragma once

#include <memory>
#include <optional>
#include <variant>

struct State {};
struct Config {};

constexpr auto End = nullptr;

template<typename C = Config, typename S = State>
struct Behavior : std::enable_shared_from_this<Behavior<C, S>>
{
   using OptBehavior = std::shared_ptr<Behavior<C, S>>;

   virtual OptBehavior operator()(S&) = 0;

   virtual void enter() {}
   virtual void exit() {}

   template<class T, class... A>
   OptBehavior become(A&& ... args) {
      return become<T>(*state, std::forward<A>(args)...);
   }

   template<class T, class... A>
   OptBehavior become(const S& s, A&& ... args) {
      OptBehavior t = std::make_shared<T>(std::forward<A>(args)...);
      t->state = &s;
      t->cfg(*config);
      exit();
      t->enter();
      return t;
   }

   OptBehavior remain() {
      return this->shared_from_this();
   }

protected:
   Behavior() = default;
   const C& cfg() {
      return *config;
   }
   void cfg(const C& c) { config = &c; }

private:
   const C* config = nullptr;
   const S* state;
};

template<typename C = Config, typename S = State>
struct Operation : public Behavior<C, S>
{
   using OptBehavior = typename Behavior<C, S>::OptBehavior;

   virtual void exec(S& s) = 0;

   explicit Operation(OptBehavior caller) : caller(caller) {}
   OptBehavior operator()(S& s) final {
      exec(s);
      return caller;
   }

private:
   OptBehavior caller;
};


template<typename M, typename S>
struct fsm
{
   const S& current() { return state; }

   template<typename E>
   void handle(E&& e) {
      M& m = static_cast<M&>(*this);
      auto next = std::visit([&](auto& s) -> std::optional<S> { return m.on_event(s, std::forward<E>(e)); }, state);
      if(next) state = *std::move(next);
   }

private:
   S state;
};
