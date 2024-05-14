#ifndef CHARACTER_STATS_H
#define CHARACTER_STATS_H

typedef std::uint16_t pointtype;  // 2^16 - 1 equals 65,535 (unsigned)
typedef std::uint16_t stattype; //


class CharacterStats
{
public:
    CharacterStats(): m_strength(1u), m_intellect(1u)
    {
        name = __func__;
    }

    CharacterStats(
        const stattype strength,
        const stattype intellect
    ): m_strength(strength), m_intellect(intellect)
    {
        name = __func__;
    }
    virtual ~CharacterStats() = default;

    [[nodiscard]] stattype get_strength() const
    {
        return m_strength;
    }

    [[nodiscard]] stattype get_intellect() const
    {
        return m_intellect;
    }

protected:
    void increase_stats(const stattype strength, const stattype intellect)
    {
        m_strength += strength;
        m_intellect += intellect;
    }

public:
    const char* name;

private:
    stattype m_strength;
    stattype m_intellect;
};


class PointStack // I can't stand PointWell, aghrr
{
public:
    PointStack(): m_current(1u), m_initial(1u) {};
    PointStack(const pointtype current, const pointtype max)
    : m_current(current), m_initial(max)
    {
        if (current > max)
            m_current = max;
    };

    bool set_max(const pointtype new_max_points)
    {
        if (new_max_points < 1)
            return false;

        m_initial = new_max_points;

        if (m_current > m_initial)
            m_current = m_initial;

        return true;
    }

    [[nodiscard]] pointtype get_initial() const
    {
        return m_initial;
    }

    [[nodiscard]] pointtype get_current() const
    {
        return m_current;
    }

    void reduce(const pointtype amount)
    {
        if (amount > m_current)
        {
            m_current = 0;
            return;
        }
        m_current -= amount;
    }

    void increase(const pointtype amount)
    {
        if (amount + m_current > m_initial)
        {
            m_current = m_initial;
            return;
        }
        m_current += amount;
    }

private:
    pointtype m_current;
    pointtype m_initial; // stands for MaxHP;
};

#endif //CHARACTER_STATS_H
